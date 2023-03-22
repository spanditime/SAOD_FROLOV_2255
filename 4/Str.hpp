#include <cstring>

class Str{
private:
	char *cp;
public:
	Str(){
		cp = new char[1]{0};
	}
	Str(const char* p){
		if(p){
			cp = new char[strlen(p)+1];
			strcpy(cp,p);
		}else
			Str();
	}
	Str(const Str &s){
		Str(s.cp);
	}
	~Str(){
		delete[] cp;
	}
	operator const char*()const{
		return cp;
	}
	const Str& operator=(const Str&s){
		if(&s == this) return *this;
		delete cp;
		strcpy(cp,s.cp);
		return *this;
	}
	Str& operator+=(const char*p){
		char *c = new char[strlen(p)+strlen(cp)+1];
		strcpy(c,cp);
		strcat(c,p);
		delete[] cp;
		cp = c;
		return *this;
	}
	Str operator+(const char*p)const{
		char *c = new char[strlen(p)+strlen(cp)+1];
		strcpy(c,cp);
		strcat(c,p);
		Str ret = Str(c);
		delete[] c;
		return ret;
	}
};
