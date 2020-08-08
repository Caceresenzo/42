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

#include <iostream>
#include <cstdlib>

#include "FragTrap.hpp"

int
main(void)
{
	srand(time(0));

	std::cout << "--- Waking up\n" << std::endl;
	FragTrap fragTrap("Unit 1");

	std::cout << "\n--- Attacks\n" << std::endl;
	fragTrap.rangedAttack("The Kind");
	fragTrap.meleeAttack("The Queen");

	std::cout << "\n--- Take damage and be repaired\n" << std::endl;
	fragTrap.takeDamage(10);
	fragTrap.beRepaired(10);
	// Energy = 95

	std::cout << std::endl;
	fragTrap.takeDamage(50);
	fragTrap.beRepaired(100);
	// Energy = 50

	std::cout << std::endl;
	fragTrap.takeDamage(50);
	fragTrap.beRepaired(100);
	// Energy = 5

	std::cout << std::endl;
	fragTrap.takeDamage(15);
	fragTrap.beRepaired(15); // Needed 10
	// Energy = -5 --> not enought

	std::cout << "\n--- Taking a lot of damage\n" << std::endl;
	fragTrap.takeDamage(1000);

	std::cout << "\n--- Waking up 2\n" << std::endl;
	FragTrap fragTrap2("Unit 2");

	std::cout << "\n--- Testing VaultHunter.EXE\n" << std::endl;
	fragTrap2.vaulthunter_dot_exe("Human");
	fragTrap2.vaulthunter_dot_exe("Sorcerer");
	fragTrap2.vaulthunter_dot_exe("Knight");
	fragTrap2.vaulthunter_dot_exe("Giant");
	fragTrap2.vaulthunter_dot_exe("Ant");

	std::cout << "\n--- END OF FILE\n" << std::endl;
}
