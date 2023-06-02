#include <iostream>
#include <memory>
#include "../Test.hpp"

using namespace std;

weak_ptr<Test> wp;

int main(){
	{
		cout<< "{\n";
		auto sp = make_shared<Test>();
		cout << "\tUseCount=" << sp.use_count() << std::endl;
		wp = sp;
		cout << "\tUseCount=" << sp.use_count() << std::endl;
		auto p = wp.lock();
		if(p){
			cout<<"\tobject owned\n";
		}else{
			cout<<"\tobject ISN'T owned\n";
		}
		cout << "\tUseCount=" << p.use_count() << std::endl;
	}
	cout<<"}\n";
	cout << "UseCount=" << wp.use_count() << std::endl;
	auto p = wp.lock();
	if(p){
		cout<<"object owned\n";
	}else{
		cout<<"object ISN'T owned\n";
	}
	cout << "UseCount=" << wp.use_count() << std::endl;
	return 0;
}
