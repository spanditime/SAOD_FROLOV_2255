#include "Str.hpp"
#include <iostream>


using namespace std;

void Test(Str s){

}

int main(){
	Str str = "a1234567890";
	Test(str);
	cout << str + str << endl;
	Str t;
	t = str;
	return 0;
}

