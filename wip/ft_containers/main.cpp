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

//#include <List.hpp>
//#include <Utility.hpp>
#include <iostream>
#include <string>

#include "Map.hpp"

//struct node
//{
//		node *left, *right, *parent;
//};
//node*
//iterate(node *p)
//{
//	node *next, *prev;
//	next = p->right;
//	if (next)
//	{
//		do
//		{
//			p = next;
//			next = p->left;
//		}
//		while (next);
//	}
//	else
//	{
//		do
//		{
//			prev = p;
//			p = p->parent;
//		}
//		while (p->left != prev);
//	}
//	return p;
//}

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
				std::cout << this << ": construct default" << std::endl;
		}

		CountAware(int hello) :
				_x(hello),
				_last("construct custom")
		{
			total++;

			if (says)
				std::cout << this << ": construct custom (" << _x << ")" << std::endl;
		}

		CountAware(const CountAware &other) :
				_x(other._x),
				_last("construct copy")
		{
			total++;

			if (says)
				std::cout << this << ": construct copy (" << _x << ")" << std::endl;
		}

		~CountAware()
		{
			total--;

			if (says)
				std::cout << this << ": destructor (" << _x << ", last: " << _last << ")" << std::endl;
		}

		CountAware&
		operator =(const CountAware &other)
		{
			_last = "assign";

			if (says)
				std::cout << this << ": operator = (" << _x << " -> " << other._x << ")" << std::endl;

			_x = other._x;
			return (*this);
		}

		bool
		operator ==(const CountAware &other) const
		{
			return (_x == other._x);
		}

		bool
		operator <(const CountAware &other) const
		{
			return (_x < other._x);
		}

		void
		say(void) const
		{
			std::cout << this << ": hey " << x() << ", last: " << last() << ", at " << (void*)this << std::endl;
		}

		int
		x() const
		{
			return (_x);
		}

		std::string
		last() const
		{
			return (_last);
		}
};

int CountAware::total = 0;
//bool CountAware::says = false;
bool CountAware::says = true;

std::ostream&
operator <<(std::ostream &stream, const CountAware &aware)
{
	return (stream << "hey " << aware.x() << ", last: " << aware.last() << ", at " << (void*)&aware);
}

typedef CountAware T;
//typedef ft::List<T> LIST;
//typedef std::list<T> LIST;

//	{
//		LIST l;
//
//		l.push_back(1);
//		l.push_back(2);
//		l.push_back(3);
//		l.push_back(4);
//
//	//	l.resize(4);
//
//		LIST ll(l);
//
//		LIST::reverse_iterator rit = ll.rbegin();
//		LIST::reverse_iterator rite = ll.rend();
//
//		while (rit != rite)
//		{
//			rit->say();
//			rit++;
//		}
//	}
//
//	{
//		ft::Map<std::string, std::string> x;
//		ft::pair< std::string, std::string> p = ft::make_pair("Hello", "World");
//		x.insert(p);
////		x[CountAware(42)] = CountAware(24);
//	}

//	typedef ft::Map<int, double> map;
//	typedef map::iterator iterator;
//	typedef map::reverse_iterator reverse_iterator;
//
//	map x;
//	ft::pair<iterator, bool> y;
//
//	for (int i = 0; i < 10; i++)
//		x.insert(ft::make_pair(i, 0.0));
//
//	std::cout << x.size() << std::endl;
//
//	x.dump();
//
////	x.erase(x.m_root->right());
//	x.erase(5);
//	x.erase(7);
//	x.erase(6);
//	x.erase(1);
//	x.erase(3);
//
//	x.dump();
//
//	for (reverse_iterator it = x.rbegin(); it != x.rend(); it++)
//		std::cout << it->first << std::endl;
////
////	for (iterator it = ft::next(x.begin(), 5); it != x.begin(); it--)
////		std::cout << it->first << std::endl;

//	ft::Map<char, int> mymap;
//	ft::Map<char, int>::iterator itlow, itup;
//
//	mymap['a'] = 20;
//	mymap['b'] = 40;
//	mymap['c'] = 60;
//	mymap['d'] = 80;
//	mymap['e'] = 100;
//
//	itlow = mymap.lower_bound('b'); // itlow points to b
//	itup = mymap.upper_bound('d'); // itup points to e (not d!)
//
//	mymap.erase(itlow, itup); // erases [itlow,itup)
//
//	// print content:
//	for (ft::Map<char, int>::iterator it = mymap.begin(); it != mymap.end(); ++it)
//		std::cout << it->first << " => " << it->second << '\n';

//	ft::List<int> lst;
//
//	lst.push_back(2);
//	lst.push_back(1);
//	lst.push_back(4);
//	lst.push_back(3);
//
//	lst.sort();
//
//	for (ft::List<int>::iterator it = lst.begin(); it != lst.end(); it++)
//	{
//		std::cout << *it << std::endl;
//	}

#include <map>

int
main(int argc, char **argv)
{
//#define NS std
//	typedef std::map<int, int> map_type;

#define NS ft
	typedef ft::Map<int, int> map_type;

	map_type map;

	std::cout << map.empty() << std::endl;
	std::cout << map.size() << std::endl;

	map_type::iterator it = map.begin();
	map_type::const_iterator cit = map.begin();

	std::cout << (it == cit) << std::endl;

//
//	map.insert(NS::make_pair(1, 0));
//	map.insert(NS::make_pair(2, 0));
//	map.insert(NS::make_pair(3, 0));

//	std::cout << ft::next(map.begin(), 0).base_node() << std::endl;
//	std::cout << ft::next(map.begin(), 1).base_node() << std::endl;
//	std::cout << ft::next(map.begin(), 2).base_node() << std::endl;
//	std::cout << ft::next(map.begin(), 3).base_node() << std::endl;
//	std::cout << ft::next(map.begin(), 4).base_node() << std::endl;
//	std::cout << ft::next(map.end(), 0).base_node() << std::endl;
//
//	for (map_type::reverse_iterator it = map.rbegin(); it != map.rend(); it++)
//		std::cout << it->first << std::endl;
//
//	map.erase(map.begin(), ft::next(map.begin(), 2));

//	map.dump();

//	map_type::iterator it = map.begin();
//	for (; it != map.end(); it++)
//		std::cout << it->first << std::endl;
//	while (1)
//	{
//		std::cout << (it++)->first << " :: " << (it == map.end() ? " END " : "") << std::endl;
//	}

//	std::cout << ft::next(map.begin(), 0).node() << std::endl;
//	std::cout << ft::next(map.begin(), 1).node() << std::endl;
//	std::cout << ft::next(map.begin(), 2).node() << std::endl;
//	std::cout << ft::next(map.begin(), 3).node() << std::endl;

//	map.dump();

//
//	std::cerr << "Remaining: " << CountAware::total << std::endl;
	return (0);
}

