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

ScavTrap::ScavTrap(void) : ClapTrap()
{
	return ;
}

ScavTrap::ScavTrap(std::string name) : ClapTrap(name)
{
	this->_energyPoints = 50;
	this->_maxEnergyPoints = 50;
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

ScavTrap::ScavTrap(const ScavTrap &other) : ClapTrap(other)
{
	*this = other;

	std::cout << this->_name << ": assigned!" << std::endl;
}

ScavTrap::~ScavTrap(void)
{
	std::cout << this->_name << ": destroyed!" << std::endl;
}

ScavTrap &
ScavTrap::operator =(const ScavTrap &right)
{
	ClapTrap::operator =(right);

	if (this != &right)
	{
		std::memcpy(&(this->_challenges), &(right._challenges), sizeof(this->_challenges));
	}

	std::cout << this->_name << ": assigned!" << std::endl;

	return (*this);
}

void
ScavTrap::challengeNewcomer(std::string const &target)
{
	std::string challenge = this->_challenges[rand() % 5];

	std::cout << this->_name << ": challenged " << target << " with " << challenge << "." << std::endl;
}
