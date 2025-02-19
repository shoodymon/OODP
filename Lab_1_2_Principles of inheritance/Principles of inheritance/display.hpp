#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include "management_system.hpp"

void displayAllCarpets(CarpetItem* carpets[], int size) {
    std::cout << "\n========= Информация о коврах =========" << std::endl;
    for (int i = 0; i < size; i++) {
        if (carpets[i] != nullptr) {
            std::cout << "Ковер #" << (i + 1) << ":" << std::endl;
            carpets[i]->showDetails();
            std::cout << std::endl;
        }
    }
    std::cout << "Общее количество ковров: " << CarpetItem::getTotalCarpets() << std::endl;
    std::cout << "=======================================" << std::endl;
}

#endif // DISPLAY_HPP
