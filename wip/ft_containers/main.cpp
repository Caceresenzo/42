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
		int _x;
		std::string _last;

	public:
		static int total;
		static bool says;

		CountAware() :
				_x(0),
				_last("construct default")
		{
			total++;

			if (says)
				std::cout << "construct default" << std::endl;
		}

		CountAware(int hello) :
				_x(hello),
				_last("construct custom")
		{
			total++;

			if (says)
				std::cout << "construct custom (" << _x << ")" << std::endl;
		}

		CountAware(const CountAware &other) :
				_x(other._x),
				_last("construct copy")
		{
			total++;

			if (says)
				std::cout << "construct copy (" << _x << ")" << std::endl;
		}

		~CountAware()
		{
			total--;

			if (says)
				std::cout << "destructor (" << _x << ", last: " << _last << ")" << std::endl;
		}

		CountAware&
		operator =(const CountAware &other)
		{
			_last = "assign";

			if (says)
				std::cout << "operator = (" << _x << " -> " << other._x << ")" << std::endl;

			_x = other._x;
			return (*this);
		}

		bool
		operator ==(const CountAware &other) const
		{
			return (_x == other._x);
		}

		void
		say(void) const
		{
			std::cout << "hey " << _x << ", last: " << _last << ", at " << (void*)this << std::endl;
		}

		int
		x() const
		{
			return (_x);
		}
};

int CountAware::total = 0;
//bool CountAware::says = false;
bool CountAware::says = true;

void
test(CountAware const &to)
{
	CountAware *x = std::allocator<CountAware>().allocate(3);

	for (int i = 0; i < 3; ++i)
		::new (&x[i]) CountAware(to);

	for (int i = 0; i < 3; ++i)
		x[i].~CountAware();
}

#define XASSERT(cond) std::cout << #cond << ": " << (cond) << std::endl;

int
main(int argc, char **argv)
{
//	{
//		ft::Vector<Aware<int> > v(100);
//
//		v.resize(50);
//		XASSERT(v.size() == 50);
//		XASSERT(v.capacity() == 100);
//
//		v.resize(200);
//		XASSERT(v.size() == 200);
//		XASSERT(v.capacity() >= 200);
//	}
	{
//		ft::Vector<CountAware> v(100);

//		v.resize(50, 1);
//		XASSERT(v.size() == 50);
//		XASSERT(v.capacity() == 100);
//		XASSERT(v == ft::Vector<CountAware>(50));

//		bool x = v == ft::Vector<CountAware>(50);
//		(void)x;

		typedef ft::Vector<int> V;

		V x(6, 42);
		V::iterator it = x.begin() + 3;
		V::iterator ite = x.end();

		V::difference_type diff = it - ite;

		std::cout << diff << std::endl;

//		v.resize(200, 1);
//		XASSERT(v.size() == 200);
//		XASSERT(v.capacity() >= 200);

//		for (unsigned i = 0; i < 50; ++i)
//			XASSERT(v[i] == CountAware(0));
//
//		for (unsigned i = 50; i < 200; ++i)
//			XASSERT(v[i] == CountAware(1));
	}
//
//	std::cout << std::endl;
//	std::cout << "TOTAL: " << CountAware::total << std::endl;
//	std::cout << std::endl;
}
