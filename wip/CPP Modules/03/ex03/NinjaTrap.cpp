/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NinjaTrap.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 11:33:26 by ecaceres          #+#    #+#             */
/*   Updated: 2020/01/08 11:33:26 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

#include "NinjaTrap.hpp"

NinjaTrap::NinjaTrap(void) : ClapTrap()
{
	return ;
}

NinjaTrap::NinjaTrap(std::string name) : ClapTrap(name)
{
	this->_hitPoints = 60;
	this->_maxHitPoints = 60;
	this->_energyPoints = 120;
	this->_maxEnergyPoints = 120;
	this->_level = 1;
	this->_name = name;
	this->_meleeAttackDamage = 60;
	this->_rangedAttackDamage = 5;
	this->_armorDamageReduction = 0;

	std::string specials[4][5] = {
		{
			"1_A",
			"1_B",
			"1_C",
			"1_D",
			"1_E",
		},
		{
			"2_A",
			"2_B",
			"2_C",
			"2_D",
			"2_E",
		},
		{
			"3_A",
			"3_B",
			"3_C",
			"3_D",
			"3_E",
		},
		{
			"4_A",
			"4_B",
			"4_C",
			"4_D",
			"4_E",
		}
	};

	std::memcpy(&(this->_specials), &specials, sizeof(specials));

	std::cout << this->_name << ": ready i will!" << std::endl;
}

NinjaTrap::NinjaTrap(NinjaTrap const &other) : ClapTrap(other)
{
	*this = other;

	std::cout << this->_name << ": copied!" << std::endl;
}

NinjaTrap::~NinjaTrap(void)
{
	std::cout << this->_name << ": destroyed!" << std::endl;
}

NinjaTrap &
NinjaTrap::operator =(const NinjaTrap &right)
{
	std::memcpy(&(this->_specials), &right._specials, sizeof(right._specials));

	return (*this);
}

void
NinjaTrap::ninjaShoebox(FragTrap &target)
{
	std::cout << this->_name << ": attacked a FragTrap named " << target.getName() << " with " << this->_specials[0][rand() % 5] << "." << std::endl;
}

void
NinjaTrap::ninjaShoebox(ScavTrap &target)
{
	std::cout << this->_name << ": attacked a ScavTrap named " << target.getName() << " with " << this->_specials[1][rand() % 5] << "." << std::endl;
}

void
NinjaTrap::ninjaShoebox(NinjaTrap &target)
{
	std::cout << this->_name << ": attacked a NinjaTrap named " << target.getName() << " with " << this->_specials[2][rand() % 5] << "." << std::endl;
}

void
NinjaTrap::ninjaShoebox(ClapTrap &target)
{
	std::cout << this->_name << ": attacked a ClapTrap named " << target.getName() << " with " << this->_specials[3][rand() % 5] << "." << std::endl;
}
