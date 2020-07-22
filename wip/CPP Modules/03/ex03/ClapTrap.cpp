/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 12:58:52 by ecaceres          #+#    #+#             */
/*   Updated: 2020/01/07 12:58:52 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>

#include "ClapTrap.hpp"

ClapTrap::ClapTrap(void) :
        _hitPoints(100),
        _maxHitPoints(100),
        _energyPoints(50),
        _maxEnergyPoints(50),
        _level(1),
        _name("unnamed"),
        _meleeAttackDamage(20),
        _rangedAttackDamage(15),
        _armorDamageReduction(3)
{
	saysm("ready! (default)");
}

ClapTrap::ClapTrap(long hitPoints, long maxHitPoints, long energyPoints, long maxEnergyPoints, long level, std::string name, long meleeAttackDamage, long rangedAttackDamage, long armorDamageReduction) :
        _hitPoints(hitPoints),
        _maxHitPoints(maxHitPoints),
        _energyPoints(energyPoints),
        _maxEnergyPoints(maxEnergyPoints),
        _level(level),
        _name(name),
        _meleeAttackDamage(meleeAttackDamage),
        _rangedAttackDamage(rangedAttackDamage),
        _armorDamageReduction(armorDamageReduction)
{
	saysm("ready!");
}

ClapTrap::ClapTrap(const ClapTrap &other)
{
	*this = other;

	saysm("copied!");
}

ClapTrap::~ClapTrap(void)
{
	saysm("destroyed!");
}

ClapTrap&
ClapTrap::operator =(const ClapTrap &other)
{
	if (this != &other)
	{
		this->_hitPoints = other._hitPoints;
		this->_maxEnergyPoints = other._hitPoints;
		this->_energyPoints = other._energyPoints;
		this->_maxEnergyPoints = other._maxEnergyPoints;
		this->_level = other._level;
		this->_name = other._name;
		this->_meleeAttackDamage = other._meleeAttackDamage;
		this->_rangedAttackDamage = other._rangedAttackDamage;
		this->_armorDamageReduction = other._armorDamageReduction;
	}

	saysm("assigned!");

	return (*this);
}

std::ostream&
ClapTrap::says()
{
	return (std::cout << "<CL4P-TP " << this->_name << "> ");
}

std::ostream&
ClapTrap::saysm(std::string msg)
{
	return (says() << msg << std::endl);
}

void
ClapTrap::rangedAttack(std::string const &target)
{
	says() << "I expect you to die " << target << "! (damage: " << this->_rangedAttackDamage << ")" << std::endl;
}

void
ClapTrap::meleeAttack(std::string const &target)
{
	says() << "Take that " << target << "! (damage: " << this->_meleeAttackDamage << ")" << std::endl;
}

void
ClapTrap::takeDamage(unsigned int amount)
{
	long damage = amount - this->_armorDamageReduction;

	if (damage <= 0)
	{
		saysm("Nice shield, maiden!");
		return;
	}

	if (damage >= this->_hitPoints)
	{
		this->_hitPoints = 0;

		saysm("The robot is dead, long live the robot!");
	}
	else
	{
		this->_hitPoints -= damage;

		says() << "Hey, watch out! (damage took: " << damage << ")" << std::endl;
	}
}

void
ClapTrap::beRepaired(unsigned int amount)
{
	long real = amount;
	if (this->_hitPoints + real > this->_maxHitPoints)
		real = this->_maxHitPoints - this->_hitPoints;

	if (this->_energyPoints < real)
		saysm("Crap! (not enought energy)");
	else
	{
		this->_energyPoints -= real;
		this->_hitPoints += real;

		says() << "Sweet energy juice! (repaired: " << real << ")." << std::endl;
	}
}

long&
ClapTrap::getEnergyPoints()
{
	return (_energyPoints);
}

long&
ClapTrap::getHitPoints()
{
	return (_hitPoints);
}

const std::string&
ClapTrap::getName()
{
	return (_name);
}
