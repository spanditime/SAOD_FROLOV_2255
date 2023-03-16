#include "Test.hpp"
#include <iostream>

using namespace std;
int idx = 0;
int Test::count = 0;
Test::Test(){
	
	cout << "Test"<<(id=idx++)<< " was created, count=" << ++count << endl;
}
Test::~Test(){
	cout<< "Test"<<id<< " was destroyed, count=" << --count << endl;
}
