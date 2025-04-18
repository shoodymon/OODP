#pragma once
#include "includes.hpp"

class ManualBuilder;

class CarManual
{
	friend class ManualBuilder;
private:
	std::string m_engine_manual;
	std::string m_brand_manual;
	std::string m_color_manual;
	std::string m_computer_manual;
	std::string m_gps_manual;

public:
	CarManual()
	{

	}

	void show_manual()
	{
		std::cout << "\t\tMANUAL\n";
		std::cout << m_brand_manual << std::endl;
		std::cout << m_engine_manual << std::endl;
		std::cout << m_color_manual << std::endl;
		std::cout << m_computer_manual << std::endl;
		std::cout << m_gps_manual << std::endl << std::endl;
	}
};
