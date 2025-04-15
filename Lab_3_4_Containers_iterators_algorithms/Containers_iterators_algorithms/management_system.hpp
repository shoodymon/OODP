#ifndef MANAGEMENT_SYSTEM_HPP
#define MANAGEMENT_SYSTEM_HPP

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

class ICarpet {
public:
    virtual ~ICarpet() {}
	virtual void getInformation() const = 0;
};

class CarpetItem : public ICarpet {
private:
	std::string m_name;
	double m_carpetSize;
	double m_price;
	static int m_totalCarpets;
public:
    // Стандартный конструктор
    CarpetItem() : m_name(""), m_carpetSize(0.0), m_price(0.0) {
        m_totalCarpets++;
    }

    // Конструктор с параметрами
    CarpetItem(const std::string& name, double carpetSize, double price)
        : m_name(name), m_carpetSize(carpetSize), m_price(price) {
        m_totalCarpets++;
    }

    // Конструктор копирования
    CarpetItem(const CarpetItem& other)
        : m_name(other.m_name), m_carpetSize(other.m_carpetSize), m_price(other.m_price) {
        m_totalCarpets++;
    }

    // Виртуальный деструктор
    virtual ~CarpetItem() {
        m_totalCarpets--;
    }

    // Оператор присваивания
    CarpetItem& operator=(const CarpetItem& other) {
        if (this != &other) {
            m_name = other.m_name;
            m_carpetSize = other.m_carpetSize;
            m_price = other.m_price;
        }
        return *this;
    }

    // Чисто виртуальный метод для отображения деталей
    virtual void showDetails() const = 0;

    // Метод для обновления количества ковров (в данном случае цены)
    void updatePrice(double amount) {
        m_price += amount;
    }

    // Статический метод для получения общего количества ковров
    static int getTotalCarpets() {
        return m_totalCarpets;
    }

    // Реализация метода из интерфейса
    void getInformation() const override {
        std::cout << "Клиент: " << m_name << ", Размер ковра: " << m_carpetSize
            << " кв.м, Цена: " << m_price << " руб." << std::endl;
    }

    // Геттеры
    std::string getName() const { return m_name; }
    double getCarpetSize() const { return m_carpetSize; }
    double getPrice() const { return m_price; }

    // Сеттеры
    void setName(const std::string& newName) { m_name = newName; }
    void setCarpetSize(double newSize) { m_carpetSize = newSize; }
    void setPrice(double newPrice) { m_price = newPrice; }
};

// Инициализация статической переменной
int CarpetItem::m_totalCarpets = 0;

// Производный класс WoolCarpet
class WoolCarpet : public CarpetItem {
private:
    std::string m_woolType;
public:
    // Стандартный конструктор
    WoolCarpet() : CarpetItem(), m_woolType("none") {}

    // Конструктор с параметрами
    WoolCarpet(const std::string& name, double carpetSize, double price, const std::string& woolType)
        : CarpetItem(name, carpetSize, price), m_woolType(woolType) {}

    // Деструктор
    ~WoolCarpet() override {}

    // Переопределение метода showDetails
    void showDetails() const override {
        std::cout << "=== Шерстяной ковер ===" << std::endl;
        getInformation();
        //std::cout << "Тип шерсти: " << m_woolType << std::endl;
        std::cout << "========================" << std::endl;
    }

    // Переопределение метода getInformation
    void getInformation() const override {
        CarpetItem::getInformation();
        std::cout << "Тип шерсти: " << m_woolType << std::endl;
    }

    // Геттер и сеттер
    std::string getWoolType() const { return m_woolType; }
    void setWoolType(const std::string& newWoolType) { m_woolType = newWoolType; }
};

// Производный класс SyntheticCarpet
class SyntheticCarpet : public CarpetItem {
private:
    std::string m_material;

public:
    // Стандартный конструктор
    SyntheticCarpet() : CarpetItem(), m_material("none") {}

    // Конструктор с параметрами
    SyntheticCarpet(const std::string& name, double carpetSize, double price, const std::string& material)
        : CarpetItem(name, carpetSize, price), m_material(material) {}

    // Деструктор
    ~SyntheticCarpet() override {}

    // Переопределение метода showDetails
    void showDetails() const override {
        std::cout << "=== Синтетический ковер ===" << std::endl;
        getInformation();
        //std::cout << "Материал: " << m_material << std::endl;
        std::cout << "============================" << std::endl;
    }

    // Переопределение метода getInformation
    void getInformation() const override {
        CarpetItem::getInformation();
        std::cout << "Материал: " << m_material << std::endl;
    }

    // Геттер и сеттер
    std::string getMaterial() const { return m_material; }
    void setMaterial(const std::string& newMaterial) { m_material = newMaterial; }
};

class CarpetManager {
private:
    std::vector<CarpetItem*> carpets;
public:
    ~CarpetManager() {
        for (auto carpet : carpets) {
            delete carpet;
        }
        carpets.clear();
    }

    void addCarpet(CarpetItem* carpet) {
        carpets.push_back(carpet);
    }

    void removeCarpet(size_t index) {
        if (index < carpets.size()) {
            delete carpets[index];
            carpets.erase(carpets.begin() + index);
        }
    }

    size_t getCount() const {
        return carpets.size();
    }

    void increasePricesByPercentage(double percentage) {
        std::for_each(carpets.begin(), carpets.end(),
            [percentage](CarpetItem* carpet) {
                carpet->updatePrice(carpet->getPrice() * percentage / 100.0);
            });
    }

    std::vector<CarpetItem*> findExpensiveCarpets(double threshold) {
        std::vector<CarpetItem*> result;
        std::copy_if(carpets.begin(), carpets.end(), std::back_inserter(result),
            [threshold](CarpetItem* carpet) {
                return carpet->getPrice() > threshold;
            });
        return result;
    }

    void sortByPrice() {
        std::sort(carpets.begin(), carpets.end(),
            [](CarpetItem* a, CarpetItem* b) {
                return a->getPrice() < b->getPrice();
            });
    }

    void displayAllCarpets() const {
        std::cout << "\n========= Информация о коврах =========" << std::endl;
        for (const auto carpet : carpets) {
            carpet->showDetails();
            std::cout << std::endl;
        }
        std::cout << "Общее количество ковров: " << CarpetItem::getTotalCarpets() << std::endl;
        std::cout << "=======================================" << std::endl;
    }

    // Получение итератора на начало
    auto begin() { return carpets.begin(); }

    // Получение итератора на конец
    auto end() { return carpets.end(); }
};

#endif // MANAGEMENT_SYSTEM_HPP