#include <iostream>

using namespace std;


void Swap(int*p1, int*p2){
    int swp = *p1;
    *p1 = *p2;
    *p2 = swp;
}

int main(){
    int a = 2, b = 3;
    cout << a << " " << b << endl;
    Swap(&a, &b);
    cout << a << " " << b << endl;
    return 0;
}
