#include <iostream>
#include <climits>

using namespace std;

int main() {
    int num = 25;
    int *intptr;
    intptr = &num;
    cout << intptr;
    return 0;
}