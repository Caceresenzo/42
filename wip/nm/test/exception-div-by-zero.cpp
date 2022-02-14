/// from https://www.guru99.com/cpp-exceptions-handling.html

#include <iostream>
using namespace std;

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
		cout << c << endl;
	}
	catch (const char *message)
	{
		cerr << message << endl;
	}
	return 0;
}
