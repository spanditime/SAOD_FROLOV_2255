#include <iostream>

using namespace std;

int main(){
    int x = 3;
    int *p = &x;
    cout << x << " " << *p << " " << p << endl;
    p++;
    cout << p << endl;
    cout << p - &x << endl;
    return 0;
}
