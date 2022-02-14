/// from https://www.guru99.com/cpp-exceptions-handling.html

#include <iostream>
#include <exception>
using namespace std;

class newException :
		public exception
{
		virtual const char*
		what() const throw ()
		{
			return "newException occurred";
		}
} newex;

int
main()
{

	try
	{
		throw newex;
	}
	catch (exception &ex)
	{
		cout << ex.what() << '\n';
	}
	return 0;
}
