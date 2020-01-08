/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FragTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 12:58:52 by ecaceres          #+#    #+#             */
/*   Updated: 2020/01/07 12:58:52 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>

#include "FragTrap.hpp"

FragTrap::FragTrap(void) : ClapTrap()
{
	return ;
}

FragTrap::FragTrap(std::string name) : ClapTrap(name)
{
	this->_energyPoints = 100;
	this->_maxEnergyPoints = 100;
	this->_name = name;
	this->_meleeAttackDamage = 30;
	this->_rangedAttackDamage = 20;
	this->_armorDamageReduction = 5;

	std::string vaulthunterAttacks[] = {
		"Fireball",
		"Waterball",
		"Airball",
		"Earthball",
		"Lightball"
	};

	long vaulthunterDamages[] = {
		10,
		12,
		2,
		23,
		1
	};

	std::memcpy(&(this->_vaulthunterAttacks), &vaulthunterAttacks, sizeof(vaulthunterAttacks));
	std::memcpy(&(this->_vaulthunterDamages), &vaulthunterDamages, sizeof(vaulthunterDamages));

	std::cout << this->_name << ": ready!" << std::endl;
}

FragTrap::FragTrap(const FragTrap &other) : ClapTrap(other)
{
	*this = other;

	std::cout << this->_name << ": assigned!" << std::endl;
}

FragTrap::~FragTrap(void)
{
	std::cout << this->_name << ": destroyed!" << std::endl;
}

FragTrap &
FragTrap::operator =(const FragTrap &right)
{
	ClapTrap::operator =(right);

	if (this != &right)
	{
		std::memcpy(&(this->_vaulthunterAttacks), &(right._vaulthunterAttacks), sizeof(this->_vaulthunterAttacks));
		std::memcpy(&(this->_vaulthunterDamages), &(right._vaulthunterDamages), sizeof(this->_vaulthunterDamages));
	}

	std::cout << this->_name << ": assigned!" << std::endl;

	return (*this);
}

void
FragTrap::vaulthunter_dot_exe(std::string const &target)
{
	int random = rand() % 5;

	std::string attack = this->_vaulthunterAttacks[random];
	long damage = this->_vaulthunterDamages[random];

	if (this->_energyPoints >= 25)
	{
		this->_energyPoints -= 25;
		std::cout << this->_name << ": attacked " << target << " with " << attack << " and do " << damage << " damage(s)." << std::endl;
	}
	else
	{
		std::cout << this->_name << ": not enought energy point to use vaulthunter_dot_exe on " << target << "." << std::endl;
	}
}
