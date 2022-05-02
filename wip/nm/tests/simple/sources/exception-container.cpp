/// from https://www.guru99.com/cpp-exceptions-handling.html

#include <iostream>
#include <vector>

int
main()
{
	std::vector<int> vec;
	vec.push_back(0);
	vec.push_back(1);
	// access the third element, which doesn't exist
	try
	{
		vec.at(2);
	}
	catch (std::exception &ex)
	{
		std::cout << "Exception occurred!" << std::endl;
	}
	return 0;
}
