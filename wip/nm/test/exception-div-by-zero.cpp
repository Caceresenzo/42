/// from https://www.guru99.com/cpp-exceptions-handling.html

#include <iostream>

double
zeroDivision(int x, int y)
{

	if (y == 0)
	{
		throw "Division by Zero!";
	}
	return (x / y);
}

int
main()
{
	int a = 11;
	int b = 0;
	double c = 0;

	try
	{
		c = zeroDivision(a, b);
		std::cout << c << std::endl;
	}
	catch (const char *message)
	{
		std::cerr << message << std::endl;
	}
	return 0;
}
