#include <iostream>
#include <string>

int main(void)
{
	std::cout << "What is your name?";
	std::string name;
	std::cin >> name;
	std::cout << "Hello, " << name << ", how old are you?";
	int age;
	std::cin >> age;
	std::cout << "Good bye, " << name << ". I'm glad you are " << age << "\n";

	return 0;
}