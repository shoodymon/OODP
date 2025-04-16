#pragma once
#include <iostream>

using std::string;

class IObserver {
public:
	virtual ~IObserver() {};
	virtual void Update(const string& msg_from_subject) = 0;
};
