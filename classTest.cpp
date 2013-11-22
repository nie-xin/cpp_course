#include <iostream>

class Demo
{
    int x, y;

public:
    void set() {
        std::cin >> x >> y;
    }

    void display() {
        std::cout << x << '\t' << y << std::endl;
    }
};

int main() 
{
    Demo obj;
    obj.set();
    obj.display();

    return 0;
}