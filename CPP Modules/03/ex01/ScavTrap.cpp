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
#include <cstdlib>

#include "ScavTrap.hpp"

ScavTrap::ScavTrap(void) :
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
	says("ready! (default)");
}

ScavTrap::ScavTrap(std::string name) :
        _hitPoints(100),
        _maxHitPoints(100),
        _energyPoints(50),
        _maxEnergyPoints(50),
        _level(1),
        _name(name),
        _meleeAttackDamage(20),
        _rangedAttackDamage(15),
        _armorDamageReduction(3)
{
	says("ready!");
}

ScavTrap::ScavTrap(const ScavTrap &other)
{
	*this = other;

	says("copied!");
}

ScavTrap::~ScavTrap(void)
{
	says("destroyed!");
}

ScavTrap&
ScavTrap::operator =(const ScavTrap &other)
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

	says("assigned!");

	return (*this);
}

std::ostream&
ScavTrap::says()
{
	return (std::cout << "<SC4V-TP " << this->_name << "> ");
}

std::ostream&
ScavTrap::says(std::string msg)
{
	return (says() << msg << std::endl);
}

void
ScavTrap::rangedAttack(std::string const &target)
{
	says() << "I expect you to die " << target << "! (damage: " << this->_rangedAttackDamage << ")" << std::endl;
}

void
ScavTrap::meleeAttack(std::string const &target)
{
	says() << "Take that " << target << "! (damage: " << this->_meleeAttackDamage << ")" << std::endl;
}

void
ScavTrap::takeDamage(unsigned int amount)
{
	long damage = amount - this->_armorDamageReduction;

	if (damage <= 0)
	{
		says("Nice shield, maiden!");
		return;
	}

	if (damage >= this->_hitPoints)
	{
		this->_hitPoints = 0;

		says("The robot is dead, long live the robot!");
	}
	else
	{
		this->_hitPoints -= damage;

		says() << "Hey, watch out! (damage took: " << damage << ")" << std::endl;
	}
}

void
ScavTrap::beRepaired(unsigned int amount)
{
	long real = amount;
	if (this->_hitPoints + real > this->_maxHitPoints)
		real = this->_maxHitPoints - this->_hitPoints;

	if (this->_energyPoints < real)
		says("Crap! (not enought energy)");
	else
	{
		this->_energyPoints -= real;
		this->_hitPoints += real;

		says() << "Sweet energy juice! (repaired: " << real << ")." << std::endl;
	}
}
void
ScavTrap::challengeNewcomer(std::string const &target)
{

	std::string challenges[] = {
	        "Game of Card",
	        "Game of Rolling Dice",
	        "Russian Roulette",
	        "Fly Higher that me",
	        "Sing a Song"
	};

	std::string challenge = challenges[rand() % 5];

	says() << "challenged " << target << " with " << challenge << "." << std::endl;
}
