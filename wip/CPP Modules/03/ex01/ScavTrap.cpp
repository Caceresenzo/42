/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScavTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 12:58:52 by ecaceres          #+#    #+#             */
/*   Updated: 2020/01/07 12:58:52 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>

#include "ScavTrap.hpp"

ScavTrap::ScavTrap(void)
{
	return ;
}

ScavTrap::ScavTrap(std::string name)
{
	this->_hitPoints = 100;
	this->_maxHitPoints = 100;
	this->_energyPoints = 50;
	this->_maxEnergyPoints = 50;
	this->_level = 1;
	this->_name = name;
	this->_meleeAttackDamage = 50;
	this->_rangedAttackDamage = 15;
	this->_armorDamageReduction = 3;

	std::string challenges[] = {
		"Game of Card",
		"Game of Rolling Dice",
		"Russian Roulette",
		"Fly Higher that me",
		"Sing a Song"
	};

	std::memcpy(&(this->_challenges), &challenges, sizeof(challenges));

	std::cout << this->_name << ": ready am i!" << std::endl;
}

ScavTrap::ScavTrap(const ScavTrap &other)
{
	*this = other;

	std::cout << this->_name << ": copied am i!" << std::endl;
}

ScavTrap::~ScavTrap(void)
{
	std::cout << this->_name << ": destroyed am i!" << std::endl;
}

ScavTrap &
ScavTrap::operator =(const ScavTrap &right)
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

	std::cout << this->_name << ": assigned am i!" << std::endl;

	return (*this);
}

void
ScavTrap::rangedAttack(std::string const &target)
{
	std::cout << this->_name << ": attacked ranged " << target << ", damage = " << this->_rangedAttackDamage << "." << std::endl;
}

void
ScavTrap::meleeAttack(std::string const &target)
{
	std::cout << this->_name << ": attacked melee " << target << ", damage = " << this->_meleeAttackDamage << "." << std::endl;
}

void
ScavTrap::takeDamage(unsigned int amount)
{
	long damage = amount - this->_armorDamageReduction;

	if (damage <= 0)
	{
		std::cout << this->_name << ": taken no damage i have." << std::endl;
		return ;
	}

	if (damage >= this->_hitPoints)
	{
		this->_hitPoints = 0;

		std::cout << this->_name << ": dead am i." << std::endl;
	}
	else
	{
		this->_hitPoints -= damage;

		std::cout << this->_name << ": damage i took is " << damage << "." << std::endl;
	}
}

void
ScavTrap::beRepaired(unsigned int amount)
{
	long real = amount;
	if (this->_hitPoints + real > this->_maxHitPoints)
	{
		real = this->_maxHitPoints - this->_hitPoints;
	}

	if (this->_energyPoints < real)
	{
		std::cout << this->_name << ": enought energy not." << std::endl;
	}
	else
	{
		this->_energyPoints -= real;
		this->_hitPoints += real;

		std::cout << this->_name << ": repaired am i (" << real << ")." << std::endl;
	}
}

void
ScavTrap::challengeNewcomer(std::string const &target)
{
	std::string challenge = this->_challenges[rand() % 5];

	std::cout << this->_name << ": challenged " << target << " with " << challenge << "." << std::endl;
}
