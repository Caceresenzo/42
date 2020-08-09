/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AssaultTerminator.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 19:24:23 by ecaceres          #+#    #+#             */
/*   Updated: 2020/07/21 19:24:23 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AssaultTerminator.hpp"

#include <iostream>

AssaultTerminator::AssaultTerminator()
{
	std::cout << "* teleports from space *" << std::endl;
}

AssaultTerminator::AssaultTerminator(const AssaultTerminator &other)
{
	std::cout << "* teleports from space *" << std::endl;

	this->operator =(other);
}

AssaultTerminator::~AssaultTerminator()
{
	std::cout << "I’ll be back ..." << std::endl;
}

AssaultTerminator&
AssaultTerminator::operator=(const AssaultTerminator &other)
{
	(void)other;

	return (*this);
}

ISpaceMarine*
AssaultTerminator::clone() const
{
	return (new AssaultTerminator(*this));
}

void
AssaultTerminator::battleCry() const
{
	std::cout << "This code is unclean. Purify it !" << std::endl;
}

void
AssaultTerminator::rangedAttack() const
{
	std::cout << "* does nothing *" << std::endl;
}

void
AssaultTerminator::meleeAttack() const
{
	std::cout << "* attaque with chainfists *" << std::endl;
}
