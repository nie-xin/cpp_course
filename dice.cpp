#include <iostream>
#include <cstdlib>	// C libaries
#include <ctime>

using namespace std;	

const int sides = 6;

inline int r_sides() { return (rand() % sides + 1); }

int main(void) 
{
	const int n_dice = 2;
	int d1, d2;
	srand(clock());
	cout << "\nEnter number of trials: ";
	int trials;
	cin >> trials;
	int* outcomes = new int[n_dice * sides + 1];

	return 0;
}