#include <iostream>
#include <cstdint>
using namespace std;

int main(){
    int x = 3;
    int*p = &x;
    uint8_t * pb = (uint8_t*)p;
    for(uint8_t * pt = pb; pt - pb < sizeof(int); pt++){
        cout << (int)*pt << ' '; 
    }
    cout << endl;
    return 0;
}
