#pragma once
#include "Manual.hpp"
#include "Builder.hpp"

class ManualBuilder : public Builder
{
private:
	CarManual m_manual;

public:
	ManualBuilder()
	{

	}

	void reset()
	{
		m_manual = *(new CarManual());
	}

	void set_brand(Brand brand)
	{
		m_manual.m_brand_manual = "Your car's brand is " + get_from_enum(BRAND, brand)
			+ " (poor choice btw). You can find new (I hope normal) car at https://get_normal_car.com/not_" +
			get_from_enum(BRAND, brand) + "_trash";
	}

	void set_engine(EngineType engine)
	{
		m_manual.m_engine_manual = "Your car's engine type is " + get_from_enum(ENGINE, engine)
			+ ". You can find repairing tutorials at https://get_normal_car.com/repair_" +
			get_from_enum(ENGINE, engine) + "_engine";
	}

	void set_color(Color color)
	{
		m_manual.m_color_manual = "Your car's color is " + get_from_enum(COLOR, color)
			+ " (ew, wtf is this, are you blind? ). You can send a querry for repainting at https://get_normal_car.com/repaint_this_" +
			get_from_enum(COLOR, color) + "_shit";
	}

	void set_gps(bool gps_avaliable)
	{
		if (gps_avaliable)
		{
			m_manual.m_gps_manual = "Your car has GPS access(good for you). Configuration manual: https://get_normal_car.com/gps_configuration/guide_for_dumbasses";
		}

		else
		{
			m_manual.m_gps_manual = "Your car doesn't has GPS access (your car is trash, told you)";
		}
	}

	void set_computer(bool computer_avaliable)
	{
		if (computer_avaliable)
		{
			m_manual.m_computer_manual = "Your car has trip computer. Select subscribing plan: https://get_normal_car.com/subscription/up_to_250_usd_for_nothing";
		}

		else
		{
			m_manual.m_computer_manual = "Your car doesn't has trip computer (believe me, it's better this way";
		}
	}

	CarManual get_manual()
	{
		return m_manual;
	}
};
