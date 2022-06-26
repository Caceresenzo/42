/// from https://www.cplusplus.com/doc/oldtutorial/templates/

#include <iostream>

template<class T>
	class mypair
	{
			T a, b;
		public:
			mypair(T first, T second)
			{
				a = first;
				b = second;
			}
			T
			getmax();
	};

template<class T>
	T
	mypair<T>::getmax()
	{
		T retval;
		retval = a > b ? a : b;
		return retval;
	}

int
main()
{
	mypair<int> myobject(100, 75);
	std::cout << myobject.getmax();
	return 0;
}
