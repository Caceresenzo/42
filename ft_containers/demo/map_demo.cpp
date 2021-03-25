/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_demo.cpp                                       :+:      :+:    :+:   */
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
#include "Map.hpp"

template<typename Map>
	void
	print(Map &map)
	{
		typedef typename Map::iterator iterator;

		for (iterator it = map.begin(); it != map.end(); it++)
			std::cout << it->first << " : " << it->second << std::endl;
	}

int
main(void)
{
	typedef ft::Map<int, std::string> Map;
	Map m;

	m.insert(ft::make_pair(3, "From"));
	m.insert(ft::make_pair(1, "Hello"));
	m.insert(ft::make_pair(4, "Maps"));
	m.insert(ft::make_pair(2, "World"));

	print(m);

	std::cout << std::endl << "Removing #2" << std::endl;
	m.erase(m.find(2));

	print(m);

	std::cout << std::endl << "Adding #2" << std::endl;
	m[2] = "Everyone";

	print(m);

	std::cout << std::endl << "Replacing #2" << std::endl;
	m[2] = "World";

	print(m);
}
