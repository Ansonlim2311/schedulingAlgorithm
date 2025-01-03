#include <iostream>
#include <climits>

using namespace std;

class Square {
    private:
    int side;

    public:
    Square (int s = 1) {
        cout << "Const..." << endl;
        side = s;
    }

    ~Square() {
        cout << "Destructor..." << endl;
    }
    void setSide(int v) { side = v; }
    int getSide() { return side; }
};

void print(Square &s) {
    cout << s.getSide() << endl;
    s.setSide(20);
}

int main() {
    Square sq(10);
    print(sq);
    cout << sq.getSide() << endl;

    return 0;
}