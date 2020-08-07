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
#include <cstdlib>

#include "FragTrap.hpp"

FragTrap::FragTrap(void) :
        _hitPoints(100),
        _maxHitPoints(100),
        _energyPoints(100),
        _maxEnergyPoints(100),
        _level(1),
        _name("unnamed"),
        _meleeAttackDamage(30),
        _rangedAttackDamage(20),
        _armorDamageReduction(5)
{
	says("ready! (default)");
}

FragTrap::FragTrap(std::string name) :
        _hitPoints(100),
        _maxHitPoints(100),
        _energyPoints(100),
        _maxEnergyPoints(100),
        _level(1),
        _name(name),
        _meleeAttackDamage(30),
        _rangedAttackDamage(20),
        _armorDamageReduction(5)
{
	says("ready!");
}

FragTrap::FragTrap(const FragTrap &other)
{
	*this = other;

	says("copied!");
}

FragTrap::~FragTrap(void)
{
	says("destroyed!");
}

FragTrap&
FragTrap::operator =(const FragTrap &other)
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
FragTrap::says()
{
	return (std::cout << "<FR4G-TP " << this->_name << "> ");
}

std::ostream&
FragTrap::says(std::string msg)
{
	return (says() << msg << std::endl);
}

void
FragTrap::rangedAttack(std::string const &target)
{
	says() << "I expect you to die " << target << "! (damage: " << this->_rangedAttackDamage << ")" << std::endl;
}

void
FragTrap::meleeAttack(std::string const &target)
{
	says() << "Take that " << target << "! (damage: " << this->_meleeAttackDamage << ")" << std::endl;
}

void
FragTrap::takeDamage(unsigned int amount)
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
FragTrap::beRepaired(unsigned int amount)
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
FragTrap::vaulthunter_dot_exe(std::string const &target)
{
	static const std::string attacks[] = {
	        "Fireball",
	        "Waterball",
	        "Airball",
	        "Earthball",
	        "Lightball"
	};

	static const long damages[] = {
	        10,
	        12,
	        2,
	        23,
	        1
	};

	int random = rand() % 5;

	std::string attack = attacks[random];
	long damage = damages[random];

	if (this->_energyPoints >= 25)
	{
		this->_energyPoints -= 25;
		says() << "attacked " << target << " with " << attack << " and do " << damage << " damage(s)." << std::endl;
	}
	else
		says() << "Crap! (not enought energy point to use vaulthunter_dot_exe on " << target << ")" << std::endl;
}
