#include "Complex.hpp"
#include <iostream>

using namespace std;

int main(){
	Complex *c = new Complex[5];
	c[0] = Complex();
	c[1] = 2_Im;
	c[2] = Complex(30);
	c[3] = Complex(3,10);
	c[4] = 3_Re + 2_Im;

	for(int i = 0; i < 5; i++){
		cout<<'|'<<c[i]<<"|="<<modc(c[i])<<endl;
		cout<< c[i] << "=>" << conjugate(c[i])<<endl;
		cout<< c[i] << '+' <<c[i]<<'='<<c[i]+c[i]<<endl;
		cout<< c[i] << '-' <<c[i]<<'='<<c[i]-c[i]<<endl;
		cout<< c[i] << '/' <<c[i]<<'='<<c[i]/c[i]<<endl;
		cout<< c[i] << '*' <<c[i]<<'='<<c[i]*c[i]<<endl;
		cout<<endl;
	}
	delete[] c;
}
