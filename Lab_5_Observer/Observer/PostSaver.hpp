#pragma once

#include <list>
#include "IPublisher.hpp"
#include "IObserver.hpp"

using std::list;
using std::cout;

class PostSaver : public IPublisher {
private:
    list<IObserver*> observers;
public:
    virtual ~PostSaver() {
        cout << "Пока, я был Издателем :)\n";
    }

    // Методы для привязки конкретных наблюдателей под это событие 
    void Add(IObserver* observer) override {
        observers.push_back(observer);
    }
    void Remove(IObserver* observer) override {
        observers.remove(observer);
    }

    // Метод для отправки сообщения всем подписанным наблюдателям
    void Send(string& msg) override {
        for (IObserver* observer : observers) {
            observer->Update(msg);
        }
    }
};
