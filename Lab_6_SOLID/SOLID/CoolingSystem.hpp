#pragma once
#include "includes.hpp"

enum class CoolingType
{
	AIR = 0,
	LIQUID,
	OIL
};
class CoolingSystem
{
private:
	CoolingType m_type;
public:
	CoolingSystem(CoolingType type = CoolingType::AIR) :
		m_type{ type }
	{

	}
	void cooling_control()
	{

	}

};
