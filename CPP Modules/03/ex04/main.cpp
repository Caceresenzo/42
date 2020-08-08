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

#include <cassert>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>

#include "SuperTrap.hpp"

int
main(void)
{
	srand(time(0));

	std::cout << "--- Waking up\n" << std::endl;
	FragTrap fragTrap("The Fragger");
	NinjaTrap ninjaTrap("The Ninja");

	std::cout << "\n--- Waking up SUPER\n" << std::endl;
	std::string name = "The BEST";
	SuperTrap superTrap(name);

	std::cout << "\n--- Assert\n" << std::endl;
	assert(superTrap.getHitPoints() == fragTrap.getHitPoints());
	assert(superTrap.getMaxHitPoints() == fragTrap.getMaxHitPoints());
	assert(superTrap.getEnergyPoints() == ninjaTrap.getEnergyPoints());
	assert(superTrap.getMaxEnergyPoints() == ninjaTrap.getMaxEnergyPoints());
	assert(superTrap.getLevel() == 1);
	assert(superTrap.getName() == name);
	assert(superTrap.getMeleeAttackDamage() == ninjaTrap.getMeleeAttackDamage());
	assert(superTrap.getRangedAttackDamage() == fragTrap.getRangedAttackDamage());
	assert(superTrap.getArmorDamageReduction() == fragTrap.getArmorDamageReduction());

	std::cout << "ok!" << std::endl;

	std::cout << "\n--- Testing ClapTrap generic attack\n" << std::endl;
	superTrap.rangedAttack("The Kind");
	superTrap.meleeAttack("The Queen");

	std::cout << "\n--- Testing FragTrap vaulthunter_dot_exe attack\n" << std::endl;
	superTrap.vaulthunter_dot_exe("The Knight");

	std::cout << "\n--- Testing NinjaTrap ninjaShoebox attack\n" << std::endl;
	superTrap.ninjaShoebox(fragTrap);

	std::cout << "\n--- END OF FILE\n" << std::endl;
}
