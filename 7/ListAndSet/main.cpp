#include <list>
#include <set>
#include <algorithm>
#include <iostream>
#include "../Test.hpp"


int main(){
	std::list<Test> list;
	list.sort();
	list.push_back(Test());
	list.remove(Test());

	std::set<Test> set;
	set.insert(Test());
	set.insert(Test());
	std::cout << "Count = " << set.size() << std::endl;
	return 0;
}
