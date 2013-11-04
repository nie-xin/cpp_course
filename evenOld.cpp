#include <iostream>

// int main() 
// {
// 	int x;

// 	while (std::cin >> x) {
// 		if ( x % 2 != 0)
// 			std::cout << x << " is odd\n";
// 		else 
// 			std::cout << x << " is even\n";
// 	}

// 	return 0;
// }

int main() {
	int x;

	while (std::cin >> x) {
		if ( x % 2 == 0 ) 
			std::cout << x << " is even.\n";
		else
			std::cout << x << " is odd.\n";
	}

	return 0;
}