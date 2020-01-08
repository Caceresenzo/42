/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 11:03:12 by ecaceres          #+#    #+#             */
/*   Updated: 2020/01/08 11:03:12 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <iostream>
#include <string>

#include "ClapTrap.hpp"

ClapTrap::ClapTrap(void)
{
	return ;
}

ClapTrap::ClapTrap(std::string name)
{
	this->_hitPoints = 100;
	this->_maxHitPoints = 100;
	this->_level = 1;
	this->_name = name;

	std::cout << this->_name << ": [claptrap] ready!" << std::endl;
}

ClapTrap::ClapTrap(const ClapTrap &other)
{
	*this = other;

	std::cout << this->_name << ": [claptrap] copied!" << std::endl;
}

ClapTrap::~ClapTrap(void)
{
	std::cout << this->_name << ": [claptrap] destroyed!" << std::endl;
}

ClapTrap &
ClapTrap::operator =(const ClapTrap &right)
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

	std::cout << this->_name << ": [claptrap] assigned!" << std::endl;

	return (*this);
}

void
ClapTrap::rangedAttack(std::string const &target)
{
	std::cout << this->_name << ": [claptrap] ranged attacked " << target << ", damage = " << this->_rangedAttackDamage << "." << std::endl;
}

void
ClapTrap::meleeAttack(std::string const &target)
{
	std::cout << this->_name << ": [claptrap] melee attacked " << target << ", damage = " << this->_meleeAttackDamage << "." << std::endl;
}

void
ClapTrap::takeDamage(unsigned int amount)
{
	long damage = amount - this->_armorDamageReduction;

	if (damage <= 0)
	{
		std::cout << this->_name << ": [claptrap] no damage taken." << std::endl;
		return ;
	}

	if (damage >= this->_hitPoints)
	{
		this->_hitPoints = 0;

		std::cout << this->_name << ": [claptrap] dead." << std::endl;
	}
	else
	{
		this->_hitPoints -= damage;

		std::cout << this->_name << ": [claptrap] took " << damage << " of damage." << std::endl;
	}
}

void
ClapTrap::beRepaired(unsigned int amount)
{
	long real = amount;
	if (this->_hitPoints + real > this->_maxHitPoints)
	{
		real = this->_maxHitPoints - this->_hitPoints;
	}

	if (this->_energyPoints < real)
	{
		std::cout << this->_name << ": [claptrap] not enought energy." << std::endl;
	}
	else
	{
		this->_energyPoints -= real;
		this->_hitPoints += real;

		std::cout << this->_name << ": [claptrap] repaired (" << real << ")." << std::endl;
	}
}

std::string
ClapTrap::getName(void)
{
	return (this->_name);
}
