/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PowerFist.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 17:28:16 by ecaceres          #+#    #+#             */
/*   Updated: 2020/07/21 17:28:16 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PowerFist.hpp"

PowerFist::PowerFist() :
        AWeapon("Power Fist", 8, 50)
{
}

PowerFist::PowerFist(const PowerFist &other)
{
	this->operator =(other);
}

PowerFist::~PowerFist()
{
}

PowerFist&
PowerFist::operator=(const PowerFist &other)
{
	AWeapon::operator =(other);

	return (*this);
}

void
PowerFist::attack() const
{
	std::cout << "* pschhh... SBAM ! *" << std::endl;
}
