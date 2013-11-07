#include <iomanip>
#include <iostream>

int main() {
    using namespace std;

    cout << setfill('0') << setw(6) << 42 << '\n';
    cout << left << setw(6) << 42 << '\n';
    cout << setfill(' ') << left << setw(6) << 42 << '\n';
    cout << setfill('-')  << setw(4) << -42 << left << '\n';


    return 0;
}