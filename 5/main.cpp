#include <iostream>
#include "Test.hpp"

using namespace std;

Test tg;

void foo(Test t){
	cout << "foo is running\n";
}

class Child: public Test{
public:
	Child(){
		cout << "Child created\n";
	}
	~Child(){
		cout << "Child destroyed\n";
	}
};

class Agregate{
public:
	Test test;
	Agregate(){
		cout << "Agregate was created\n";
	}
	~Agregate(){
		cout << "Agregate was destroyed\n";
	}
};

class AgregateT{
public:
	Test test;
	Child child;
	AgregateT(Test t, Child c){
		cout << "AgregateT was created\n";
	}
	~AgregateT(){
		cout << "AgregateT was destroyed\n";
	}	
};

int main(){
	cout<<"Enter main\n";
	Test t;
	Child c;
	
	cout<<"Hello world!\n";
	Agregate a;
	Test *t2=new Test[2];
	foo(t2[0]);
	delete[] t2;
	cout << "Tooday is a great day\n";
	Test t3;
	cout<<"Exit main\n";
	AgregateT at(t3,c);
}
