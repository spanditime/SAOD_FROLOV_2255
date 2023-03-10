#include <iostream>


void rotate(int a[], int n,bool clockwise=false){
	int x = (clockwise)?(a[n-1]):(a[0]);
	if(clockwise){
		for(int i = n-1; i >0; i--){
			a[i]=a[i-1];
		}
	}else{
		for(int i = 1; i < n; i++){
			a[i-1] = a[i];
		}
	}
	if(clockwise){
		a[0]=x;
	}else {
		a[n-1]=x;
	}
}


int main(){
	int a[5]{1,2,3,4,5};
	for(int i = 0; i < 5; i++){
		std::cout << a[i] << ' ';
	}
	std::cout<< std::endl;
	rotate(a,5);
	for(int i = 0; i < 5; i++){
		std::cout << a[i] << ' ';
	}
	std::cout<< std::endl;
	rotate(a,5,true);
	for(int i = 0; i < 5; i++){
		std::cout << a[i] << ' ';
	}
	std::cout<< std::endl;
	return 0;
}
