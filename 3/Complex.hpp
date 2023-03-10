#include <ostream>
#include <cmath>

class Complex{
public:
	long double Re,Im;
	Complex(long double Real=0, long double Imaginary=0){
		Re = Real;Im = Imaginary;
	}

};
inline std::ostream& operator<<(std::ostream &o, const Complex &c){ 
	return o << '(' << c.Re << ", " << c.Im << ')'; 
}
inline Complex operator+(const Complex&c1, const Complex&c2){
	return Complex(c1.Re+c2.Re,c1.Im+c2.Im);
}
inline Complex operator*(const Complex&c1, const Complex&c2){
	return Complex(c1.Re*c2.Re-c1.Im*c2.Im,c1.Re*c2.Im+c2.Re*c1.Im);
}
inline Complex operator/(const Complex&c1, const Complex&c2){
	long double div=c2.Re*c2.Re+c2.Im*c2.Im;
	return Complex((c1.Re*c2.Re+c1.Im*c2.Im)/div,(-c1.Re*c2.Im+c2.Re*c1.Im)/div);
}
inline Complex operator-(const Complex&c1, const Complex&c2){
	return Complex(c1.Re-c2.Re,c1.Im-c2.Im);
}

inline Complex operator""_Re(long double Real){
	return Complex(Real);
}
inline Complex operator""_Im(long double Imaginary){
	return Complex(0,Imaginary);
}
inline Complex operator""_Re(unsigned long long Real){
	return Complex(Real);
}
inline Complex operator""_Im(unsigned long long Imaginary){
	return Complex(0,Imaginary);
}
inline Complex conjugate(const Complex&c){
	return Complex(c.Re,-c.Im);
}
inline long double modc(const Complex&c){
	return std::sqrt(c.Re*c.Re+c.Im*c.Im);
}
