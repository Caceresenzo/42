/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 16:09:13 by ecaceres          #+#    #+#             */
/*   Updated: 2020/07/21 16:09:13 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cstdlib>
#include <iostream>

#include "Peon.hpp"
#include "Sorcerer.hpp"
#include "Victim.hpp"

int
main()
{
	Sorcerer robert("Robert", "the Magnificent");

	Victim jim("Jimmy");
	Peon joe("Joe");

	std::cout << robert << jim << joe;

	robert.polymorph(jim);
	robert.polymorph(joe);

	std::cout << "--- EXTRA ---" << std::endl;

	jim.getPolymorphed();
	joe.getPolymorphed();

	{
		Victim *jimByCopy = new Victim(jim);
		Peon *joeByCopy = new Peon(joe);

		delete jimByCopy;
		delete joeByCopy;
	}

	std::cout << "--- EXTRA END ---" << std::endl;

	return (EXIT_SUCCESS);
}
