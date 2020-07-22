/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TacticalMarine.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 19:24:23 by ecaceres          #+#    #+#             */
/*   Updated: 2020/07/21 19:24:23 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "TacticalMarine.hpp"

#include <iostream>

TacticalMarine::TacticalMarine()
{
	std::cout << "Tactical Marine ready for action !" << std::endl;
}

TacticalMarine::TacticalMarine(const TacticalMarine &other)
{
	std::cout << "Tactical Marine ready for action !" << std::endl;

	this->operator =(other);
}

TacticalMarine::~TacticalMarine()
{
	std::cout << "Aaargh ..." << std::endl;
}

TacticalMarine&
TacticalMarine::operator=(const TacticalMarine &other)
{
	(void)other;

	return (*this);
}

ISpaceMarine*
TacticalMarine::clone() const
{
	return (new TacticalMarine(*this));
}

void
TacticalMarine::battleCry() const
{
	std::cout << "For the Holy PLOT !" << std::endl;
}

void
TacticalMarine::rangedAttack() const
{
	std::cout << "* attacks with a bolter *" << std::endl;
}

void
TacticalMarine::meleeAttack() const
{
	std::cout << "* attacks with a chainsword *" << std::endl;
}
