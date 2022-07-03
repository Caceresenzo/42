/// from https://www.cplusplus.com/doc/oldtutorial/templates/

#include <iostream>

template<class T, int N>
	class mysequence
	{
			T memblock[N];
		public:
			void
			setmember(int x, T value);
			T
			getmember(int x);
	};

template<class T, int N>
	void
	mysequence<T, N>::setmember(int x, T value)
	{
		memblock[x] = value;
	}

template<class T, int N>
	T
	mysequence<T, N>::getmember(int x)
	{
		return memblock[x];
	}

int
main()
{
	mysequence<int, 5> myints;
	mysequence<double, 5> myfloats;
	myints.setmember(0, 100);
	myfloats.setmember(3, 3.1416);
	std::cout << myints.getmember(0) << '\n';
	std::cout << myfloats.getmember(3) << '\n';
	return 0;
}
