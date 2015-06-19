
#include "stdafx.h"

ProtocolReceiver::ProtocolReceiver(EQNet* net)
	: AckManager(net)
{

}

bool ProtocolReceiver::handleProtocol(uint32_t len)
{
	readPacket(getBuffer(), len);
	return hasQueuedPackets();
}

void ProtocolReceiver::readPacket(byte* data, uint32_t len, bool fromCombined)
{
	uint16_t opcode = toHostShort(*(uint16_t*)data);

	if (opcode > 0xFF)
	{
		// raw packet, no protocol
		queueRawPacket(data, len);
		return;
	}

	uint32_t offset = 2;

	switch (opcode)
	{
	case OP_SessionResponse:
	{
#ifdef EQNET_DEBUG
		printf("OP_SessionResponse\n");
#endif
		SessionResponse* sr = (SessionResponse*)(data + 2);
		uint32_t crcKey = toHostLong(sr->key);

		setCRCKey(crcKey);
		mEQNet->awaitingSession = false;
		mEQNet->retryCount = 0;

		switch (mEQNet->mode)
		{
		case MODE_LOGIN:
		{
			// send session ready packet
			Packet* packet = new Packet(nullptr, 12, OP_SessionReady);
			byte* b = packet->getDataBuffer();
			b[0] = 2;
			b[10] = 8;

			packet->queue(mEQNet);
			break;
		}

		case MODE_LOGIN_TO_WORLD:
		{
			// echo session response to the server
			sendRaw(data, len);
			setAutoAckEnabled(true);

			// struct seems to be the same for all client versions
			Packet* packet = new Packet(mEQNet, sizeof(Titanium::LoginInfo_Struct), EQNET_OP_SendLoginInfo);
			Titanium::LoginInfo_Struct* li = (Titanium::LoginInfo_Struct*)packet->getDataBuffer();

			// login_info -> accountID as a string, null terminator, session key
			memset(li->login_info, 0, 64);
			itoa(getAccountID(), li->login_info, 10);
			memcpy(&li->login_info[strlen(li->login_info) + 1], getSessionKey().c_str(), getSessionKey().length());

			packet->queue(mEQNet);
			queueEvent(mEQNet, EQNET_EVENT_LoginToWorld);
			break;
		}

		case MODE_WORLD_TO_ZONE:
		{
			// echo session response to the server
			sendRaw(data, len);
			setAutoAckEnabled(true);

			// struct seems to be the same for all client versions
			Packet* packet = new Packet(mEQNet,
				mEQNet->clientVersion <= EQNET_CLIENT_Underfoot ? 
					sizeof(Titanium::ClientZoneEntry_Struct) : sizeof(RoF::ClientZoneEntry_Struct),
				EQNET_OP_PlayerSpawn);
			Titanium::ClientZoneEntry_Struct* cze = (Titanium::ClientZoneEntry_Struct*)packet->getDataBuffer();

			Util::strcpy(cze->char_name, mEQNet->selectedCharacter->name, 64);

			packet->queue(mEQNet);
			queueEvent(mEQNet, EQNET_EVENT_Zoning);
			break;
		}

		default:
			// echo session response to the server
			sendRaw(data, len);
			break;
		}

#ifdef EQNET_DEBUG
		printf("server CRC key: %i (0x%0.8X)\n", getCRCKey(), getCRCKey());
#endif
		break;
	}

	case OP_Combined:
	{

		if (!validatePacket(data, len, offset, fromCombined))
			break;

		uint32_t pos = offset;
		while (pos < len)
		{
			// 8 bit packet length
			uint8_t size = data[pos];
			++pos;

			readPacket(data + pos, size, true);
			pos += size;
		}
		break;
	}

	case OP_Packet:
	{

		if (!validatePacket(data, len, offset, fromCombined))
			break;

		checkInboundPacket(data, len, offset);
		break;
	}

	case OP_Fragment:
	{
		if (!validatePacket(data, len, offset, fromCombined))
			break;

		checkInboundFragment(data, len);
		break;
	}

	case OP_Ack:
	{
		if (!validatePacket(data, len, offset, fromCombined))
			break;

		uint16_t seq = toHostShort(*(uint16_t*)(data + offset));
		receiveAck(seq);
		break;
	}

	case OP_SessionDisconnect:
		queueEvent(mEQNet, EQNET_EVENT_Disconnected);
		break;
		
	// packets we don't care about
	case OP_SessionStatResponse:
		break;

#ifdef EQNET_DEBUG
	default:
		printf("Receiver received unknown protocol opcode 0x%0.4X len: %u, fromCombined: %i\n", opcode,
			len, fromCombined ? 1 : 0);
		for (uint32_t i = 0; i < len; ++i)
			printf("%0.2X ", data[i]);
		printf("\n");
		break;
#endif
	}
}

bool ProtocolReceiver::validatePacket(byte*& packet, uint32_t& len, uint32_t& offset, bool fromCombined)
{
	// check CRC before decompressing
	if (!fromCombined && !CRC::validatePacket(packet, len, getCRCKey()))
		return false;

	// attempt to decompress
	if (packet[2] == 0x5a) // compressed
	{
		if (!Compression::decompressPacket(mEQNet, packet, len))
		{
			offset = 2;
			return true;
		}
	}
	else if (packet[2] == 0xa5) // not compressed
	{
		offset = 3;
		return true;
	}

	offset = 2;
	return true;
}
