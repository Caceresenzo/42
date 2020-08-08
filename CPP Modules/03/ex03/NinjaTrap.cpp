/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NinjaTrap.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 11:33:26 by ecaceres          #+#    #+#             */
/*   Updated: 2020/01/08 11:33:26 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "NinjaTrap.hpp"

#include <cstdlib>
#include <iostream>

NinjaTrap::NinjaTrap(void) :
        ClapTrap(60, 60, 120, 120, 1, "unnamed", 60, 5, 0)
{
	saysm("ready! (default)");
}

NinjaTrap::NinjaTrap(std::string name) :
        ClapTrap(60, 60, 120, 120, 1, name, 60, 5, 0)
{
	saysm("ready!");
}

NinjaTrap::NinjaTrap(NinjaTrap const &other) :
        ClapTrap(other)
{
	*this = other;

	saysm("copied!");
}

NinjaTrap::~NinjaTrap(void)
{
	saysm("destroyed!");
}

NinjaTrap&
NinjaTrap::operator =(const NinjaTrap &right)
{
	ClapTrap::operator =(right);

	saysm("assigned!");

	return (*this);
}

void
NinjaTrap::doNinjaShoebox(std::string type, int index, ClapTrap *clapTrapPtr)
{
	const static std::string specials[4][5] = {
	        {
	                "1_A",
	                "1_B",
	                "1_C",
	                "1_D",
	                "1_E",
	        },
	        {
	                "2_A",
	                "2_B",
	                "2_C",
	                "2_D",
	                "2_E",
	        },
	        {
	                "3_A",
	                "3_B",
	                "3_C",
	                "3_D",
	                "3_E",
	        },
	        {
	                "4_A",
	                "4_B",
	                "4_C",
	                "4_D",
	                "4_E",
	        }
	};

	std::string attack = specials[index][rand() % 5];

	says() << "attacked a " << type << " named " << clapTrapPtr->getName() << " with " << attack << "." << std::endl;
}

std::ostream&
NinjaTrap::says()
{
	return (std::cout << "<NINJ4-TP " << this->getName() << "> ");
}

void
NinjaTrap::ninjaShoebox(FragTrap &target)
{
	doNinjaShoebox("FragTrap", 0, &target);
}

void
NinjaTrap::ninjaShoebox(ScavTrap &target)
{
	doNinjaShoebox("ScavTrap", 1, &target);
}

void
NinjaTrap::ninjaShoebox(NinjaTrap &target)
{
	doNinjaShoebox("NinjaTrap", 2, &target);
}

void
NinjaTrap::ninjaShoebox(ClapTrap &target)
{
	doNinjaShoebox("ClapTrap", 3, &target);
}
