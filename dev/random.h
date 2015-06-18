
#ifndef _EQNET_RANDOM_H_
#define _EQNET_RANDOM_H_

#include <random>
#include <chrono>
#include <ctime>
#include <cstdint>

class Random : public std::mt19937
{
public:
	Random()
	{
		std::chrono::system_clock::duration usec = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch());
		seed((uint32_t)usec.count());
		//time_t time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
		//seed((uint32_t)time);
	}
};

#endif//_EQNET_RANDOM_H_
