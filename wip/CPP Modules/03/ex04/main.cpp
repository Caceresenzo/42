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

#include "FragTrap.hpp"
#include "NinjaTrap.hpp"
#include "SuperTrap.hpp"

int
main(void)
{
	srand(time(0));

	FragTrap fragTrap("The Fragger");
	NinjaTrap ninjaTrap("The Ninja");

	std::string name = "The BEST";
	SuperTrap superTrap(name);

	assert (superTrap._hitPoints == fragTrap._hitPoints);
	assert (superTrap._maxHitPoints == fragTrap._maxHitPoints);
	assert (superTrap._energyPoints == ninjaTrap._energyPoints);
	assert (superTrap._maxEnergyPoints == ninjaTrap._maxEnergyPoints);
	assert (superTrap._level == 1);
	assert (superTrap._name == name);
	assert (superTrap._meleeAttackDamage == ninjaTrap._meleeAttackDamage);
	assert (superTrap._rangedAttackDamage == fragTrap._rangedAttackDamage);
	assert (superTrap._armorDamageReduction == fragTrap._armorDamageReduction);

	superTrap.rangedAttack("The Kind");
	superTrap.meleeAttack("The Queen");

	superTrap.vaulthunter_dot_exe("The Knight");
	superTrap.ninjaShoebox(fragTrap);
}
