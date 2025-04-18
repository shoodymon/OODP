#pragma once
#include "Builder.hpp"

class Director
{
private:
	int get_random(int min, int max)
	{
		static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
		return static_cast<int>(rand() * fraction * (max - min + 1) + min);
	}


public:
	Director()
	{

	}

	void make_sport_car(Builder* builder, bool strict = true)
	{
		if (strict)
		{
			builder->set_brand(FERRARI);
			builder->set_engine(PETROL_ENGINE);
			builder->set_color(RED);
			builder->set_gps(true);
			builder->set_computer(true);
		}

		else
		{
			builder->set_brand((Brand)get_random(3, 5));
			builder->set_engine(PETROL_ENGINE);
			builder->set_color((Color)get_random(0, 4));
			builder->set_gps(true);
			builder->set_computer(true);
		}
	}

	void make_SUV_car(Builder* builder, bool strict = true)
	{
		if (strict)
		{
			builder->set_brand(NISSAN);
			builder->set_engine(HYBRID_ENGINE);
			builder->set_color(BLUE);
			builder->set_gps(false);
			builder->set_computer(false);
		}

		else
		{
			builder->set_brand((Brand)get_random(0, 2));
			builder->set_engine((EngineType)get_random(1, 3));
			builder->set_color((Color)get_random(0, 4));
			builder->set_gps(get_random(0, 1));
			builder->set_computer(get_random(0, 1));
		}
	}
};
