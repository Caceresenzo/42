/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Character.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 18:02:26 by ecaceres          #+#    #+#             */
/*   Updated: 2020/07/21 18:02:26 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Character.hpp"

Character::Character() :
        _name(""),
        _ap(DEFAULT_MAX_AP),
        _weapon(NULL)
{
}

Character::Character(std::string const &name) :
        _name(name),
        _ap(DEFAULT_MAX_AP),
        _weapon(NULL)
{
}

Character::Character(const Character &other) :
        _name(other._name),
        _ap(other._ap),
        _weapon(other._weapon)
{
}

Character::~Character()
{
}

Character&
Character::operator=(const Character &other)
{
	if (this != &other)
	{
		this->_name = other._name;
		this->_ap = other._ap;
		this->_weapon = other._weapon;
	}

	return (*this);
}

void
Character::recoverAP()
{
	if ((_ap += 10) > DEFAULT_MAX_AP)
		_ap = DEFAULT_MAX_AP;
}

void
Character::equip(AWeapon *weapon)
{
	_weapon = weapon;
}

void
Character::attack(Enemy *enemy)
{
	if (_weapon && enemy)
	{
		int after = _ap - _weapon->getAPCost();

		if (after < 0)
			return;

		std::cout << _name << " attaque " << enemy->getType() << " with a " << _weapon->getName() << std::endl;

		_weapon->attack();

		enemy->takeDamage(_weapon->getDamage());
		if (enemy->getHp() <= 0)
			delete enemy;

		_ap = after;
	}
}

int
Character::getAp() const
{
	return (_ap);
}

AWeapon*
Character::getWeapon() const
{
	return (_weapon);
}

const std::string&
Character::getName() const
{
	return _name;
}

std::ostream&
operator <<(std::ostream &stream, Character &character)
{
	stream << character.getName() << " has " << character.getAp() << " AP and ";

	if (character.getWeapon())
		stream << "carries a " << character.getWeapon()->getName();
	else
		stream << "is unarmed";

	return (stream << std::endl);
}
