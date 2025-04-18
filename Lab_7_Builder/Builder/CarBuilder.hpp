#pragma once
#include "Car.hpp"
#include "Builder.hpp"

class CarBuilder : public Builder
{
private:
	Car m_car;

public:
	CarBuilder()
	{

	}

	void reset()
	{
		m_car = *(new Car());
	}

	void set_brand(Brand brand)
	{
		m_car.m_brand = brand;
	}

	void set_engine(EngineType engine)
	{
		m_car.m_engine = engine;
	}

	void set_color(Color color)
	{
		m_car.m_color = color;
	}

	void set_gps(bool gps_avaliable)
	{
		m_car.m_gps = gps_avaliable;
	}

	void set_computer(bool computer_avalibale)
	{
		m_car.m_computer = computer_avalibale;
	}

	Car get_car()
	{
		return m_car;
	}
};
