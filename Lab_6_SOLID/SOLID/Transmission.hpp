#pragma once
#include "includes.hpp"

enum class GearboxType
{
	MANUAL = 0,
	AUTOMATIC
};

class Transmission
{
private:
	GearboxType m_gearbox;
	unsigned short int m_gears;

public:
	Transmission(GearboxType gearbox = GearboxType::MANUAL, unsigned short int gears = 5) :
		m_gearbox{ gearbox },
		m_gears{ gears }
	{

	}

	void transmission_control()
	{

	}
};
