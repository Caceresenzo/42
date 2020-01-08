/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*    SuperTrap.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 11:52:40 by ecaceres          #+#    #+#             */
/*   Updated: 2020/01/08 11:52:40 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <iostream>

#include "SuperTrap.hpp"

SuperTrap::SuperTrap(void) : ClapTrap(), FragTrap(), NinjaTrap()
{
	return ;
}

SuperTrap::SuperTrap(std::string name) : ClapTrap(name), FragTrap(name), NinjaTrap(name)
{
	this->_hitPoints = 100;
	this->_maxHitPoints = 100;
	this->_energyPoints = 120;
	this->_maxEnergyPoints = 120;
	this->_level = 1;
	this->_name = name;
	this->_meleeAttackDamage = 60;
	this->_rangedAttackDamage = 20;
	this->_armorDamageReduction = 5;

	std::cout << this->_name << ": SUPER READY!" << std::endl;
}

SuperTrap::SuperTrap(SuperTrap const &other) : ClapTrap(other), FragTrap(other), NinjaTrap(other)
{
	*this = other;

	std::cout << this->_name << ": copied!" << std::endl;
}

SuperTrap::~SuperTrap(void)
{
	std::cout << this->_name << ": destroyed!" << std::endl;
}

SuperTrap &
SuperTrap::operator =(const SuperTrap &right)
{
	ClapTrap::operator =(right);
	FragTrap::operator =(right);
	NinjaTrap::operator =(right);

	return (*this);
}

void
SuperTrap::rangedAttack(std::string const &target)
{
	FragTrap::rangedAttack(target);
}

void
SuperTrap::meleeAttack(std::string const &target)
{
	NinjaTrap::meleeAttack(target);
}
