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
        ClapTrap(100, 100, 50, 50, 1, "unnamed", 20, 15, 3)
{
	saysm("ready! (default)");
}

ScavTrap::ScavTrap(std::string name) :
        ClapTrap(100, 100, 50, 50, 1, name, 20, 15, 3)
{
	saysm("ready!");
}

ScavTrap::ScavTrap(const ScavTrap &other)
{
	*this = other;

	saysm("copied!");
}

ScavTrap::~ScavTrap(void)
{
	saysm("destroyed!");
}

ScavTrap&
ScavTrap::operator =(const ScavTrap &other)
{
	ClapTrap::operator =(other);

	saysm("assigned!");

	return (*this);
}

std::ostream&
ScavTrap::says()
{
	return (std::cout << "<SC4V-TP " << this->getName() << "> ");
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
