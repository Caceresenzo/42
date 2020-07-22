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
#include "ScavTrap.hpp"

int
main(void)
{
	srand(time(0));

	std::cout << "--- Waking up\n" << std::endl;
	ScavTrap scavTrap("Unit 1");
	FragTrap fragTrap("Unit 1");

	std::cout << "\n--- Attacks\n" << std::endl;
	scavTrap.rangedAttack("The Kind");
	scavTrap.meleeAttack("The Queen");
	fragTrap.rangedAttack("The Kind");
	fragTrap.meleeAttack("The Queen");

	std::cout << "\n--- Take damage and be repaired\n" << std::endl;
	scavTrap.takeDamage(10); // HP = 93, Energy = 50
	scavTrap.beRepaired(10); // HP = 100, Energy = 43

	std::cout << std::endl;
	scavTrap.takeDamage(20); // HP = 83, Energy = 43
	scavTrap.beRepaired(100); // HP = 100, Energy = 26

	std::cout << std::endl;
	scavTrap.takeDamage(40); // HP = 63, Energy = 26
	scavTrap.beRepaired(26); // HP = 89, Energy = 0
	scavTrap.beRepaired(1); // Needed 1, so not enough

	std::cout << "\n--- Taking a lot of damage\n" << std::endl;
	scavTrap.takeDamage(1000);

	std::cout << "\n--- Waking up 2\n" << std::endl;
	ScavTrap scavTrap2("Unit 2");

	std::cout << "\n--- Testing VaultHunter.EXE\n" << std::endl;
	scavTrap2.challengeNewcomer("Human");
	scavTrap2.challengeNewcomer("Sorcerer");
	scavTrap2.challengeNewcomer("Knight");
	scavTrap2.challengeNewcomer("Giant");
	scavTrap2.challengeNewcomer("Ant");

	std::cout << "\n--- END OF FILE\n" << std::endl;
}
