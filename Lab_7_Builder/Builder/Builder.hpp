#pragma once
#include "includes.hpp"

class Builder
{
public:
	virtual ~Builder()
	{

	}


	virtual void reset() = 0;

	virtual void set_brand(Brand brand) = 0;
	virtual void set_engine(EngineType engine) = 0;
	virtual void set_color(Color color) = 0;
	virtual void set_gps(bool gps_avaliable) = 0;
	virtual void set_computer(bool computer_avalibale) = 0;
};
