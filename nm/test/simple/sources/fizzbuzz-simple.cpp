/// from https://www.delftstack.com/howto/cpp/fizzbuzz-in-cpp/

#include <iostream>

const int COUNT = 100;

int
main()
{

	for (int i = 1; i <= COUNT; ++i)
	{

		if (i % 3 == 0)
			std::cout << "Fizz, ";
		else if (i % 5 == 0)
			std::cout << "Buzz, ";
		else if (i % 15 == 0)
			std::cout << "FizzBuzz, ";
		else
			std::cout << i << ", ";

	}

	return 0;
}
