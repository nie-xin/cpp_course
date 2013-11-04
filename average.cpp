#include <iostream>

int main()
{
	int sum(0);
	int count(0);
	int x;

	while(std::cin >> x) {
		sum = sum + x;
		count = count + 1;
	}

	if ( count == 0) {
		std::cout << "error - count: " << count << std::endl;
		return -1;
	} else {
		std::cout << "average = " << sum/count << '\n';
	}
}