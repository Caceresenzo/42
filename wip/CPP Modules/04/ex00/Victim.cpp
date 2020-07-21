/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Victim.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 12:18:41 by ecaceres          #+#    #+#             */
/*   Updated: 2020/07/21 12:18:41 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Victim.hpp"

Victim::Victim()
{
}

Victim::Victim(std::string name) :
        _name(name)
{
	std::cout << "A random victim called " << _name << " just appeared!" << std::endl;
}

Victim::Victim(const Victim &other) :
        _name(other._name)
{
	std::cout << "A random victim called " << _name << " just appeared!" << std::endl;
}

Victim::~Victim()
{
	std::cout << "The victim " << _name << " died for no apparent reasons!" << std::endl;
}

Victim&
Victim::operator=(const Victim &other)
{
	if (this != &other)
	{
		this->_name = other._name;
	}

	return (*this);
}

void
Victim::getPolymorphed() const
{
	std::cout << _name << " was just polymorphed in a cute little sheep!" << std::endl;
}

const std::string&
Victim::getName() const
{
	return _name;
}

std::ostream&
operator <<(std::ostream &stream, Victim &victim)
{
	return (stream << "I'm " << victim.getName() << " and I like otters!" << std::endl);
}
