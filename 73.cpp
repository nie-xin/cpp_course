#include <iostream>
#include <ostream>

int main() 
{
	std::cout << '+';
	for (int i(0); i != 20; ++i)
		std::cout << '-';
	std::cout << '-';

	for (int i(0); i != 3; ++i)
		std::cout << ' ';
	std::cout << "Hello, reader!";

	for (int i(0); i != 20; ++i)
		std::cout << '-';
	std::cout << "+\n";
}
