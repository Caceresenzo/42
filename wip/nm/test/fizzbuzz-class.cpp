/// from https://www.delftstack.com/howto/cpp/fizzbuzz-in-cpp/

#include <iostream>
#include <map>
#include <string>
#include <utility>

const int COUNT = 100;

class FizzBuzz
{
		std::map<int, std::string> table;
	public:
		explicit
		FizzBuzz(std::map<int, std::string> &init) :
				table(init)
		{
		}

		void
		checkFizzBuzz()
		{
			for (int i = 1; i <= COUNT; ++i)
			{
				for (std::map<int, std::string>::iterator item = table.begin(); item != table.end(); ++item)
				{
					i % item->first == 0 ? std::cout << item->second << ", " : std::cout << i << ", ";
					break;
				}
			}
		}
};

int
main()
{
	std::map<int, std::string> init;
	init[3] = "Fizz";
	init[5] = "Buzz";
	init[15] = "FizzBuzz";

	FizzBuzz fii(init);
	fii.checkFizzBuzz();

	return 0;
}
