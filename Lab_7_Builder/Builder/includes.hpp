#pragma once

#include <iostream>
#include <string>
#include <vector>

enum EngineType
{
	PETROL_ENGINE = 0,
	GAS_ENGINE,
	HYBRID_ENGINE,
	ELECTRIC
};

enum Brand
{
	NISSAN = 0,
	KIA,
	VOLKSWAGEN,
	FORD,
	FERRARI,
	LAMBORGINI
};

enum Color
{
	BLUE,
	BLACK,
	RED,
	YELLOW,
	WHITE
};


enum Enums
{
	BRAND = 0,
	ENGINE,
	COLOR
};

std::string get_from_enum(int enum_type, int enum_value)
{
	if (enum_type == BRAND)
	{
		switch (enum_value)
		{
		case(NISSAN):     return "Nissan";			break;
		case(KIA):        return "Kia";				break;
		case(VOLKSWAGEN): return "Volkswagen";		break;
		case(FORD):		  return "Ford";			break;
		case(FERRARI):	  return "Ferrari";			break;
		case(LAMBORGINI): return "Lamborgini";		break;
		}
	}

	else if (enum_type == ENGINE)
	{
		switch (enum_value)
		{
		case(PETROL_ENGINE):    return "Petrol";		break;
		case(HYBRID_ENGINE):    return "Hybrid";		break;
		case(ELECTRIC):			return "Electric";		break;
		}
	}

	else if (enum_type == COLOR)
	{
		switch (enum_value)
		{
		case(BLUE):     return "Blue";		break;
		case(BLACK):    return "Black";		break;
		case(RED):		return "Red";		break;
		case(YELLOW):   return "Yellow";	break;
		case(WHITE):	return "White";		break;

		}
	}
}
