#pragma once
#include <iostream>

class Test{
private:
	static int count;
	int id;

public:
	int value;
	Test(){
		value = 0;
		id = count++;
		std::cout << "Test " << id << " created" << std::endl;
	}
	~Test(){
		std::cout << "Test " << id << " destroyed" << std::endl;
	}
	bool operator<(const Test&test) const {
		return value < test.value;
	}
	bool operator==(const Test&test) const {
		return value == test.value;
	}
};
int Test::count=0;
