/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AMateria.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 11:20:50 by ecaceres          #+#    #+#             */
/*   Updated: 2020/07/22 11:20:50 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AMateria.hpp"

AMateria::AMateria() :
        _type(""),
        _xp(0)
{
}

AMateria::AMateria(const std::string &type) :
        _type(type),
        _xp(0)
{
}

AMateria::AMateria(const AMateria &other) :
        _type(other._type),
        _xp(0)
{
}

AMateria::~AMateria()
{
}

AMateria&
AMateria::operator=(const AMateria &other)
{
	if (this != &other)
	{
		this->_type = other._type;
		this->_xp = other._xp;
	}

	return (*this);
}

void
AMateria::use(ICharacter &target)
{
	(void)target;

	this->_xp += 10;
}

const std::string&
AMateria::getType() const
{
	return _type;
}

unsigned int
AMateria::getXp() const
{
	return _xp;
}
