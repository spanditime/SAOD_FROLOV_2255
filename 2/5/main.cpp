#include <iostream>

using namespace std;

int main(){
	int a[5]{1,2,3,4,5};
	for(int i = 0; i < 5; i++){
		cout << a[i] << ' ';
	}
	cout<< endl;

	for(int *p = a; p-a<5; p++){
		cout << *p << ' ';
	}
	cout<<endl;

	return 0;
}
