#include "ManualBuilder.hpp"
#include "CarBuilder.hpp"
#include "Director.hpp"

int main()
{
	srand(time(0));

	CarBuilder* car_builder = new CarBuilder();
	ManualBuilder* manual_builder = new ManualBuilder;
	Director* director = new Director;

	director->make_sport_car(car_builder);
	Car sport_car = car_builder->get_car();
	sport_car.print_information();


	director->make_sport_car(manual_builder);
	CarManual sport_manual = manual_builder->get_manual();
	sport_manual.show_manual();

}
