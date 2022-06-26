/// from https://www.guru99.com/cpp-exceptions-handling.html

#include <iostream>
#include <exception>

class newException :
		public std::exception
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
	catch (std::exception &ex)
	{
		std::cout << ex.what() << '\n';
	}
	return 0;
}
