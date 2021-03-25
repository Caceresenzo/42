/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_demo.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 18:17:50 by ecaceres          #+#    #+#             */
/*   Updated: 2020/09/29 18:17:50 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>

#include "Iterator.hpp"
#include "List.hpp"

template<typename List>
	void
	print(List &list)
	{
		typedef typename List::iterator iterator;

		for (iterator it = list.begin(); it != list.end(); it++)
			std::cout << *it << "  ";
		std::cout << std::endl;
	}

int
main(void)
{
	typedef ft::List<std::string> Lst;
	Lst l;

	l.push_back("Hello");
	l.push_back("World");
	l.push_back("From");
	l.push_back("Lists");

	print(l);

	std::cout << std::endl << "Adding Duplicates" << std::endl;
	l.push_back("Hello");
	l.push_back("World");

	print(l);

	std::cout << std::endl << "Sorting" << std::endl;
	l.sort();

	print(l);

	std::cout << std::endl << "Unique" << std::endl;
	l.unique();

	print(l);
}
