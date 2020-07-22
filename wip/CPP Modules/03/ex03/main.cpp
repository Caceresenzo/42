/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 10:18:19 by ecaceres          #+#    #+#             */
/*   Updated: 2020/01/08 10:18:19 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cstdlib>
#include <ctime>
#include <iostream>

#include "FragTrap.hpp"
#include "NinjaTrap.hpp"
#include "ScavTrap.hpp"

int
main(void)
{
	srand(time(0));

	std::cout << "--- Waking up\n" << std::endl;
	FragTrap fragTrap("The Fragger");
	ScavTrap scavTrap("The Scaver");
	NinjaTrap ninjaTrap("The Ninja");
	ClapTrap clapTrap(1, 1, 1, 1, 1, "The Original", 1, 1, 1);

	std::cout << "\n--- Attacks 1\n" << std::endl;
	ninjaTrap.ninjaShoebox(fragTrap);
	ninjaTrap.ninjaShoebox(scavTrap);
	ninjaTrap.ninjaShoebox(ninjaTrap);
	ninjaTrap.ninjaShoebox(clapTrap);

	std::cout << std::endl;

	std::cout << "\n--- Attacks 2\n" << std::endl;
	ninjaTrap.ninjaShoebox(fragTrap);
	ninjaTrap.ninjaShoebox(scavTrap);
	ninjaTrap.ninjaShoebox(ninjaTrap);
	ninjaTrap.ninjaShoebox(clapTrap);

	std::cout << std::endl;

	std::cout << "\n--- Attacks 3\n" << std::endl;
	ninjaTrap.ninjaShoebox(fragTrap);
	ninjaTrap.ninjaShoebox(scavTrap);
	ninjaTrap.ninjaShoebox(ninjaTrap);
	ninjaTrap.ninjaShoebox(clapTrap);

	std::cout << "\n--- END OF FILE\n" << std::endl;
}
