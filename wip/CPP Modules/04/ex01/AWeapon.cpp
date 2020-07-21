/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AWeapon.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 16:44:53 by ecaceres          #+#    #+#             */
/*   Updated: 2020/07/21 16:44:53 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AWeapon.hpp"

AWeapon::AWeapon() :
        _name(""),
        _apcost(0),
        _damage(0)
{
}

AWeapon::AWeapon(const AWeapon &other) :
        _name(other._name),
        _apcost(other._apcost),
        _damage(other._damage)
{
}

AWeapon::AWeapon(const std::string &name, int apcost, int damage) :
        _name(name),
        _apcost(apcost),
        _damage(damage)
{
}

AWeapon::~AWeapon()
{
}

AWeapon&
AWeapon::operator=(const AWeapon &other)
{
	if (this != &other)
	{
		this->_name = other._name;
		this->_apcost = other._apcost;
		this->_damage = other._damage;
	}

	return (*this);
}

int
AWeapon::getAPCost() const
{
	return _apcost;
}

int
AWeapon::getDamage() const
{
	return _damage;
}

const std::string&
AWeapon::getName() const
{
	return _name;
}
