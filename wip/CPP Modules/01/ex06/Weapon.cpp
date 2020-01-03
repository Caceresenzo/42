/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 11:32:52 by ecaceres          #+#    #+#             */
/*   Updated: 2020/01/03 11:32:56 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>

#include "Weapon.hpp"

Weapon::Weapon(std::string type)
{
	this->setType(type);
}

std::string &
Weapon::getType(void) const
{
	const std::string &ref = this->_type;
	return ((std::string &)ref);
}

void
Weapon::setType(std::string type)
{
	this->_type = type;
}
