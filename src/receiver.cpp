
#include "stdafx.h"

Receiver::Receiver(EQNet* net)
	: AckManager(net)
{

}

bool Receiver::handleProtocol(uint32_t len)
{
	readPacket(getBuffer(), len);
	return hasQueuedPackets();
}

void Receiver::readPacket(byte* data, uint32_t len, bool fromCombined)
{
	uint16_t opcode = toHostShort(*(uint16_t*)data);

	if (opcode > 0xFF)
	{
		//raw packet, no protocol
		queueRawPacket(data, len);
		return;
	}

	uint32_t offset = 2;

	switch (opcode)
	{
	case OP_SessionResponse:
	{
		printf("OP_SessionResponse\n");
		SessionResponse* sr = (SessionResponse*)(data + 2);
		uint32_t crcKey = toHostLong(sr->key);

		setCRCKey(crcKey);

		switch (mEQNet->mode)
		{
		case MODE_LOGIN:
		{
			// send session ready packet
			Packet* packet = new Packet(12, OP_SessionReady);
			byte* b = packet->getDataBuffer();
			b[0] = 2;
			b[10] = 8;

			packet->queue(mEQNet);
			break;
		}
		case MODE_WORLD:
		{
			// echo session response to the server
			sendRaw(data, len);

			// say hello to the world server
			setAutoAckEnabled(true);

			// struct seems to be the same for all client versions
			Packet* packet = new Packet(sizeof(Titanium::LoginInfo_Struct),
				translateOpcodeToServer(mEQNet, EQNET_OP_SendLoginInfo));
			Titanium::LoginInfo_Struct* li = (Titanium::LoginInfo_Struct*)packet->getDataBuffer();

			// login_info -> accountID as a string, null terminator, session key
			memset(li->login_info, 0, 64);
			itoa(getAccountID(), li->login_info, 10);
			memcpy(&li->login_info[strlen(li->login_info) + 1], getSessionKey().c_str(), getSessionKey().length());

			packet->queue(mEQNet);
			queueEvent(mEQNet, EQNET_LOGIN_TO_WORLD);
			break;
		}
		default:
			// echo session response to the server
			sendRaw(data, len);
			break;
		}

		printf("server CRC key: %i (0x%0.8X)\n", getCRCKey(), getCRCKey());
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
		queueEvent(mEQNet, EQNET_DISCONNECTED);
		break;
		
	// packets we don't care about
	case OP_SessionStatResponse:
		break;

	default:
		printf("Receiver received unknown protocol opcode 0x%0.4X len: %u, fromCombined: %i\n", opcode,
			len, fromCombined ? 1 : 0);
		for (uint32_t i = 0; i < len; ++i)
			printf("%0.2X ", data[i]);
		printf("\n");
		break;
	}
}

bool Receiver::validatePacket(byte*& packet, uint32_t& len, uint32_t& offset, bool fromCombined)
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
	else if (packet[2] == 0xa5) // Not compressed, single byte flag
	{
		offset = 3;
		return true;
	}

	offset = 2;
	return true;
}
