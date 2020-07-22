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

SuperTrap::SuperTrap(void) :
        ClapTrap(100, 100, 120, 120, 1, "unnamed", 60, 20, 5),
        FragTrap(),
        NinjaTrap()
{
	saysm("ready! (default)");
}

SuperTrap::SuperTrap(std::string name) :
        ClapTrap(100, 100, 120, 120, 1, name, 60, 20, 5),
        FragTrap(),
        NinjaTrap()
{
	saysm("ready!");
}

SuperTrap::SuperTrap(SuperTrap const &other) :
        ClapTrap(other),
        FragTrap(other),
        NinjaTrap(other)
{
	*this = other;

	saysm("copied!");
}

SuperTrap::~SuperTrap(void)
{
	saysm("destroyed!");
}

std::ostream&
SuperTrap::says()
{
	return (std::cout << "<SUP3R-TP " << this->FragTrap::getName() << "> ");
}

SuperTrap&
SuperTrap::operator =(const SuperTrap &right)
{
	FragTrap::operator =(right);
	NinjaTrap::operator =(right);

	return (*this);
}
