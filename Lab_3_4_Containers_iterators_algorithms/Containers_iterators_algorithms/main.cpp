#include "management_system.hpp"

int main() {
	setlocale(0, "");
	system("chcp1251");
	system("cls");

    CarpetManager manager;

    manager.addCarpet(new WoolCarpet("Иванов", 3.5, 2000.0, "овечья"));
    manager.addCarpet(new WoolCarpet("Петров", 2.8, 1800.0, "альпака"));
    manager.addCarpet(new WoolCarpet("Сидоров", 4.2, 2500.0, "мериносовая"));
    manager.addCarpet(new SyntheticCarpet("Кузнецов", 3.0, 1500.0, "полиэстер"));
    manager.addCarpet(new SyntheticCarpet("Смирнов", 2.5, 1200.0, "нейлон"));

    std::cout << "Первоначальная информация:" << std::endl;
    manager.displayAllCarpets();

    std::cout << "\nУвеличение цен всех ковров на 10%:" << std::endl;
    manager.increasePricesByPercentage(10);
    manager.displayAllCarpets();

    std::cout << "\nСортировка ковров по цене:" << std::endl;
    manager.sortByPrice();
    manager.displayAllCarpets();

    std::cout << "\nКовры дороже 2000 рублей:" << std::endl;
    auto expensiveCarpets = manager.findExpensiveCarpets(2000.0);
    for (const auto carpet : expensiveCarpets) {
        carpet->showDetails();
    }

    std::cout << "\nУдаляем ковёр по индексу:" << std::endl;
    manager.removeCarpet(2);
    manager.displayAllCarpets();

	return 0;
}