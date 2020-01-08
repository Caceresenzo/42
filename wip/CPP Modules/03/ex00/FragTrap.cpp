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

FragTrap::FragTrap(void)
{
	return ;
}

FragTrap::FragTrap(std::string name)
{
	this->_hitPoints = 100;
	this->_maxHitPoints = 100;
	this->_energyPoints = 100;
	this->_maxEnergyPoints = 100;
	this->_level = 1;
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

FragTrap::FragTrap(const FragTrap &other)
{
	*this = other;

	std::cout << this->_name << ": copied!" << std::endl;
}

FragTrap::~FragTrap(void)
{
	std::cout << this->_name << ": destroyed!" << std::endl;
}

FragTrap &
FragTrap::operator =(const FragTrap &right)
{
	if (this != &right)
	{
		this->_hitPoints = right._hitPoints;
		this->_maxEnergyPoints = right._hitPoints;
		this->_energyPoints = right._energyPoints;
		this->_maxEnergyPoints = right._maxEnergyPoints;
		this->_level = right._level;
		this->_name = right._name;
		this->_meleeAttackDamage = right._meleeAttackDamage;
		this->_rangedAttackDamage = right._rangedAttackDamage;
		this->_armorDamageReduction = right._armorDamageReduction;
	}

	std::cout << this->_name << ": assigned!" << std::endl;

	return (*this);
}

void
FragTrap::rangedAttack(std::string const &target)
{
	std::cout << this->_name << ": ranged attacked " << target << ", damage = " << this->_rangedAttackDamage << "." << std::endl;
}

void
FragTrap::meleeAttack(std::string const &target)
{
	std::cout << this->_name << ": melee attacked " << target << ", damage = " << this->_meleeAttackDamage << "." << std::endl;
}

void
FragTrap::takeDamage(unsigned int amount)
{
	long damage = amount - this->_armorDamageReduction;

	if (damage <= 0)
	{
		std::cout << this->_name << ": no damage taken." << std::endl;
		return ;
	}

	if (damage >= this->_hitPoints)
	{
		this->_hitPoints = 0;

		std::cout << this->_name << ": dead." << std::endl;
	}
	else
	{
		this->_hitPoints -= damage;

		std::cout << this->_name << ": took " << damage << " of damage." << std::endl;
	}
}

void
FragTrap::beRepaired(unsigned int amount)
{
	long real = amount;
	if (this->_hitPoints + real > this->_maxHitPoints)
	{
		real = this->_maxHitPoints - this->_hitPoints;
	}

	if (this->_energyPoints < real)
	{
		std::cout << this->_name << ": not enought energy." << std::endl;
	}
	else
	{
		this->_energyPoints -= real;
		this->_hitPoints += real;

		std::cout << this->_name << ": repaired (" << real << ")." << std::endl;
	}
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
