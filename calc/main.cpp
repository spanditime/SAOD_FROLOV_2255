#include <iostream>
#include <cstdlib>
#include <string.h>
#include <exception>
using namespace std;

enum Ops
{
	ADD,
	SUB,
	MUL,
	DIV
};

int calc(Ops op, int a, int s)
{
	switch (op)
	{
	case ADD:
		return a + s;
		break;
	case SUB:
		return a - s;
		break;
	case MUL:
		return a * s;
		break;
	case DIV:
		if (s != 0) return a / s;
		else throw std::invalid_argument("Cannot divide by zero");
		break;
	}
}

int conv(const char* operation, const char* a, const char* b)
{
	int f,s;
	try{
		f = std::stoi(a);
		s = std::stoi(b);
	}catch(std::invalid_argument exc){
		throw std::invalid_argument("Operands should be integer numbers");
	}
	int res = 0;
	if (strcmp(operation, "add") == 0)
		res = calc(ADD, f, s);
	else if (strcmp(operation, "mul") == 0)
		res = calc(MUL, f, s);
	else if (strcmp(operation, "sub") == 0)
		res = calc(SUB, f, s);
	else if (strcmp(operation, "div") == 0)
		res = calc(DIV, f, s);
	else throw std::invalid_argument("Invalid operation");
	return res;
}

void showHelp(){
	cout << "{calc} {first argument} [operation] {second argument} \
	Operations: \n\
	\tsub - subtraction\n\
	\tadd - addition\n\
	\tdiv - division\n\
	\tmul - multiplication\n";
}

int main(int argc, char** argv)
{
	if(argc == 4){
		try{
			int res = conv(argv[2],argv[1],argv[3]);
			cout << argv[1]<<' '<< argv[2] <<' ' << argv[3] << " = "<< res << '\n';
		}catch(std::invalid_argument exc){
			cout<< exc.what() << '\n';
			showHelp();
			return 1;
		}
	}else{
		showHelp();
		return 1;
	}
	return 0;
}
