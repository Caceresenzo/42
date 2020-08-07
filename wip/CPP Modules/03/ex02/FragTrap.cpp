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
        ClapTrap(100, 100, 100, 100, 1, "unnamed", 30, 20, 5)
{
	saysm("ready! (default)");
}

FragTrap::FragTrap(std::string name) :
        ClapTrap(100, 100, 100, 100, 1, name, 30, 20, 5)
{
	saysm("ready!");
}

FragTrap::FragTrap(const FragTrap &other)
{
	*this = other;

	saysm("copied!");
}

FragTrap::~FragTrap(void)
{
	saysm("destroyed!");
}

FragTrap&
FragTrap::operator =(const FragTrap &other)
{
	ClapTrap::operator =(other);

	saysm("assigned!");

	return (*this);
}

std::ostream&
FragTrap::says()
{
	return (std::cout << "<FR4G-TP " << this->getName() << "> ");
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

	if (this->getEnergyPoints() >= 25)
	{
		this->getEnergyPoints() -= 25;
		says() << "attacked " << target << " with " << attack << " and do " << damage << " damage(s)." << std::endl;
	}
	else
		says() << "Crap! (not enought energy point to use vaulthunter_dot_exe on " << target << ")" << std::endl;
}
