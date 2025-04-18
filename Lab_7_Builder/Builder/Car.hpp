#pragma once
#include "includes.hpp"

class CarBuilder;

class Car
{
	friend class CarBuilder;
private:
	Brand m_brand;
	EngineType m_engine;
	Color m_color;
	bool m_gps;
	bool m_computer;



public:
	Car()
	{

	}

	void print_information()
	{
		std::cout << "\t\tCAR INFORMATION\n";
		std::cout << "Brand: " + get_from_enum(BRAND, m_brand) << std::endl;
		std::cout << "Engine type: " + get_from_enum(ENGINE, m_engine) << std::endl;
		std::cout << "Color: " + get_from_enum(COLOR, m_color) << std::endl;
		std::cout << "GPS system is " << ((m_gps) ? ("") : ("not")) << "avaliable" << std::endl;
		std::cout << "Trip computer is " << ((m_gps) ? ("") : ("not")) << "avaliable" << std::endl << std::endl;
	}
};
