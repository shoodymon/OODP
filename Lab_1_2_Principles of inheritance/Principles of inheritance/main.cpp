#include "management_system.hpp"
#include "display.hpp"

int main() {
	setlocale(0, "");
	system("chcp1251");
	system("cls");

	// 2.1.Создать массив указателей на тип CarpetItem размерностью 20.
	const int ARR_SIZE = 20;
	CarpetItem* arrCarpets[ARR_SIZE];

	for (int i = 0; i < ARR_SIZE; i++) {
		arrCarpets[i] = nullptr;
	}

	// 2.2.Добавить в массив информацию о трех шерстяных коврах и двух синтетических коврах.
	arrCarpets[0] = new WoolCarpet("Иванов", 3.5, 2000.0, "овечья");
	arrCarpets[1] = new WoolCarpet("Петров", 2.8, 1800.0, "альпака");
	arrCarpets[2] = new WoolCarpet("Сидоров", 4.2, 2500.0, "мериносовая");
	arrCarpets[3] = new SyntheticCarpet("Кузнецов", 3.0, 1500.0, "полиэстер");
	arrCarpets[4] = new SyntheticCarpet("Смирнов", 2.5, 1200.0, "нейлон");

	// 2.4.Вывести информацию о всех коврах на экран.
	std::cout << "Первоначальная информация:" << std::endl;
	displayAllCarpets(arrCarpets, ARR_SIZE);

	// 2.3.Заменить данные любого элемента массива.
	delete arrCarpets[1]; // Освобождаем память перед заменой
	arrCarpets[1] = new WoolCarpet("Новиков", 3.0, 2100.0, "кашемир");

	std::cout << "\nИнформация после замены элемента:" << std::endl;
	displayAllCarpets(arrCarpets, ARR_SIZE);

	// 2.5.Увеличить цену за чистку для 1 - го и 3 - го ковров.
	arrCarpets[0]->updatePrice(500.0);
	arrCarpets[2]->updatePrice(300.0);

	// 2.6.Вывести информацию о всех коврах на экран.
	std::cout << "\nИнформация после увеличения цены для 1-го и 3-го ковров:" << std::endl;
	displayAllCarpets(arrCarpets, ARR_SIZE);

	// 2.7.Увеличить цену за чистку для 5 - го ковра.
	arrCarpets[4]->updatePrice(200.0);

	// 2.8.Снова вывести информацию о коврах на экран.
	std::cout << "\nИнформация после увеличения цены для 5-го ковра:" << std::endl;
	displayAllCarpets(arrCarpets, ARR_SIZE);

	// Освобождение памяти
	for (int i = 0; i < ARR_SIZE; i++) {
		delete arrCarpets[i];
		arrCarpets[i] = nullptr;
	}

	return 0;
}