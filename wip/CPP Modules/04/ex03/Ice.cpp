/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ice.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 11:38:40 by ecaceres          #+#    #+#             */
/*   Updated: 2020/07/22 11:38:40 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Ice.hpp"

Ice::Ice() :
        AMateria("ice")
{
}

Ice::Ice(const Ice &other) :
        AMateria(other)
{
}

Ice::~Ice()
{
}

Ice&
Ice::operator=(const Ice &other)
{
	AMateria::operator =(other);

	return (*this);
}

AMateria*
Ice::clone() const
{
	return (new Ice(*this));
}

void
Ice::use(ICharacter &target)
{
	AMateria::use(target);

	std::cout << "* shoots an ice bolt at " << target.getName() << " *" << std::endl;
}
