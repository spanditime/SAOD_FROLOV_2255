#include <iostream>
#include <cstring>

using namespace std;

int slen(char *s){
	int len = 0;
	for(;*s;s++,len++);

	return len;
}

int compare(char *s, char *t){
	for(;*s==*t && *s && *s; s++,t++);
	int d = *s - *t;
	return d;
}

int main(){
	char str[] = "Hello!";
	cout << str << endl;

	cout << strlen(str) << ' ' << sizeof(str) << endl;

	char t[32];
	for(char *pd = t, *ps = str; (*pd++ = *ps++););
	cout << t << endl;

	cout << slen(t) << ' ' << compare(t,str)<<endl;

	return 0;
}
