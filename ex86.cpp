#include <iostream>

int main()
{
    using namespace std;

    cout.setf(ios_base::right, ios_base::adjustfield);
    cout.width(4);
    cout << '*' << '|';

    for (int i(1); i < 11; ++i) {
        cout.setf(ios_base::right, ios_base::adjustfield);
        cout.width(4);
        cout << i;
    }
    cout << '\n';

    cout.fill('-');
    cout.width(4);
    cout << '-' << '+';

    for (int i(1); i < 11; ++i) {
        cout.fill('-');
        cout.width(4);
            cout << '-';
    }
    cout << '\n';

    // table
    for (int i(1); i < 11; ++i) { 
        cout.width(4);
        cout.fill(' ');
        cout.setf(ios_base::right, ios_base::adjustfield);
        cout << i << '|';
        for(int j(1); j < 11; ++j) {

            cout.setf(ios_base::right, ios_base::adjustfield);
            cout.width(4);
            cout << i*j;
        }
        cout << '\n';
    }

    return 0;
}