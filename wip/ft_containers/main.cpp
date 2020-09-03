/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 14:47:49 by ecaceres          #+#    #+#             */
/*   Updated: 2020/08/25 14:47:49 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Vector.hpp>
#include <iostream>
#include <memory>
#include <vector>
#include <test_macros.hpp>

class CountAware
{
	private:
		int _hello;
		std::string _last;

	public:
		static int total;
		static bool says;

		CountAware() :
				_hello(0),
				_last("construct default")
		{
			total++;

			if (says)
				std::cout << "construct default" << std::endl;
		}

		CountAware(int hello) :
				_hello(hello),
				_last("construct custom")
		{
			total++;

			if (says)
				std::cout << "construct custom (" << _hello << ")" << std::endl;
		}

		CountAware(const CountAware &other) :
				_hello(other._hello),
				_last("construct copy")
		{
			total++;

			if (says)
				std::cout << "construct copy (" << _hello << ")" << std::endl;
		}

		~CountAware()
		{
			total--;

			if (says)
				std::cout << "destructor (" << _hello << ", last: " << _last << ")" << std::endl;
		}

		CountAware&
		operator =(const CountAware &other)
		{
			_last = "assign";

			if (says)
				std::cout << "operator = (" << _hello << " -> " << other._hello << ")" << std::endl;

			_hello = other._hello;
			return (*this);
		}

		void
		say(void) const
		{
			std::cout << "hey " << _hello << ", last: " << _last << ", at " << (void*)this << std::endl;
		}
};

int CountAware::total = 0;
bool CountAware::says = false;
//bool CountAware::says = true;

void
test(CountAware const &to)
{
	CountAware *x = std::allocator<CountAware>().allocate(3);

	for (int i = 0; i < 3; ++i)
		::new (&x[i]) CountAware(to);

	for (int i = 0; i < 3; ++i)
		x[i].~CountAware();
}

int
main(int argc, char **argv)
{
//	std::vector<CountAware> v;
//	std::cout << (void*) &(v.front()) << std::endl;
//	std::cout << (void*) v.begin().base() << std::endl;
//
//	v.insert(v.begin(), CountAware(5));
//	std::cout << (void*) v.begin().base() << std::endl;

//	ft::Vector<int>().at(2);
//
//	v.assign(3, CountAware(5));
//	v.push_back(CountAware(1));
//	std::cout << std::endl;
//	v.push_back(CountAware(2));
//	std::cout << std::endl;
//	v.push_back(CountAware(3));
//	std::cout << std::endl;
//	v.insert(v.begin(), CountAware(6));
//	v.erase(v.begin());

//	std::cout << (void*) &(v.front()) << std::endl;
//	v.reserve(100);
//
//	std::cout << "TOTAL: " << CountAware::total << std::endl;
//	v.clear();
//
//	std::cout << "TOTAL: " << CountAware::total << std::endl;
//	std::cout << std::endl;

//	CountAware *x = std::allocator<CountAware>().allocate(3);
//	for (int i = 0; i < 3; ++i)
//	{
//		std::memcpy(&(x[i]), &cpy, sizeof(CountAware));
////		x[i] = CountAware(x[i]);
//	}

//	test(CountAware(5));
////
//	std::cout << std::endl;
//	std::cout << "TOTAL: " << CountAware::total << std::endl;
//	std::cout << std::endl;

//	ft::Vector<CountAware> ftv;
//	for (size_t i = 0; i < 50; ++i)
//	{
//		ftv.push_back(CountAware(i));
//	}
//	for (size_t i = 0; i < ftv.size(); ++i)
//	{
//		ftv[i].say();
//	}
//	ftv.pop_back();
//

//	const ft::Vector<CountAware> v;
////	v.assign(10, CountAware(1));
//
//	for (size_t i = 0; i < 50; ++i)
//	{
////		v.push_back(CountAware(i));
////		std::cout << std::endl;
//	}
//
////	ft::Vector<CountAware>::iterator it = v.begin();
//	ft::Vector<CountAware>::const_iterator cit = v.begin();
//
//	while (cit != v.end())
//	{
//		cit->say();
//		cit++;
//	}
//
//
////	v.clear();

//	std::vector<CountAware> v;
//	typedef std::vector<CountAware> vec;
	typedef ft::Vector<CountAware> vec;

	for (int i = 0; i < 6; i++)
	{
		std::cout << "\e[95m" "TESTING WITH I=" << i << "\e[0m" << std::endl;
		{
			vec v;
			for (int index = 0; index < 5; ++index)
				v.push_back(CountAware(index));

			v.insert(v.begin() + i, CountAware(123));
			//	v.insert(v.begin(), 3, CountAware(1));
			//	v.insert(v.begin(), CountAware(2));
			//	v.insert(v.begin(), CountAware(3));

			std::cout << std::endl;
			vec::iterator ite = v.end();
			for (vec::iterator it = v.begin(); it < ite; ++it)
				it->say();
		}

		std::cout << std::endl;
		std::cout << "TOTAL: " << CountAware::total << std::endl;
		std::cout << std::endl;

		if (CountAware::total)
		{
			std::cout << "WARNING: count aware total not zero, resetting it." << std::endl;
			CountAware::total = 0;
		}
	}

}
