/// from https://www.cplusplus.com/doc/oldtutorial/templates/

#include <iostream>

// class template:
template<class T>
	class mycontainer
	{
			T element;
		public:
			mycontainer(T arg)
			{
				element = arg;
			}
			T
			increase()
			{
				return ++element;
			}
	};

// class template specialization:
template<>
	class mycontainer<char>
	{
			char element;
		public:
			mycontainer(char arg)
			{
				element = arg;
			}
			char
			uppercase()
			{
				if ((element >= 'a') && (element <= 'z'))
					element += 'A' - 'a';
				return element;
			}
	};

int
main()
{
	mycontainer<int> myint(7);
	mycontainer<char> mychar('j');
	std::cout << myint.increase() << std::endl;
	std::cout << mychar.uppercase() << std::endl;
	return 0;
}
