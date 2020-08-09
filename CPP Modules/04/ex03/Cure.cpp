/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cure.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 11:38:40 by ecaceres          #+#    #+#             */
/*   Updated: 2020/07/22 11:38:40 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cure.hpp"

Cure::Cure() :
        AMateria("cure")
{
}

Cure::Cure(const Cure &other) :
        AMateria(other)
{
}

Cure::~Cure()
{
}

Cure&
Cure::operator=(const Cure &other)
{
	AMateria::operator =(other);

	return (*this);
}

AMateria*
Cure::clone() const
{
	return (new Cure(*this));
}

void
Cure::use(ICharacter &target)
{
	AMateria::use(target);

	std::cout << "* heals " << target.getName() << "'s wounds *" << std::endl;
}
