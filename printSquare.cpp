#include <iostream>
#include <iomanip>

int main()
{
	std::cout << "N	N^2	N^3\n";
	for (int i(1); i != 21; ++i) {
		// std::cout << i << '\t' << i*i << '\t' << i*i*i << '\n';
		std::cout << std::setw(2) << i
				  << std::setw(6) << i*i
				  << std::setw(7) << i*i*i
				  << '\n';
	}

	return 0;
}
