#pragma once
#include <iostream>
#include "IObserver.hpp"

using std::cout;

class NotificationObserver : public IObserver {
public:
    virtual ~NotificationObserver() {}

    void Update(const string& msg_from_subject) override {
        cout << "Сообщение от издателя: " << msg_from_subject << "\n\n";
    }

};
