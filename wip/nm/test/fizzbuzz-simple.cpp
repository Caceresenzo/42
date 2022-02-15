/// from https://www.delftstack.com/howto/cpp/fizzbuzz-in-cpp/

#include <iostream>

using std::cout;
using std::endl;

constexpr int COUNT = 100;

int
main()
{

	for (int i = 1; i <= COUNT; ++i)
	{

		if (i % 3 == 0)
			cout << "Fizz, ";
		else if (i % 5 == 0)
			cout << "Buzz, ";
		else if (i % 15 == 0)
			cout << "FizzBuzz, ";
		else
			cout << i << ", ";

	}

	return EXIT_SUCCESS;
}
