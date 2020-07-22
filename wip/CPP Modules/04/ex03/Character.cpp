/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Character.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 11:46:06 by ecaceres          #+#    #+#             */
/*   Updated: 2020/07/22 11:46:06 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Character.hpp"

Character::Character() :
        _name("")
{
	zeroInventory();
}

Character::Character(std::string name) :
        _name(name)
{
	zeroInventory();
}

Character::Character(const Character &other) :
        _name(other._name)
{
	zeroInventory();

	this->operator =(other);
}

Character::~Character()
{
	for (int index = 0; index < INVENTORY_SIZE; ++index)
	{
		AMateria *&at = _inventory[index];

		if (at)
			delete at;

		at = NULL;
	}
}

Character&
Character::operator=(const Character &other)
{
	if (this != &other)
	{
		this->_name = other._name;

		for (int index = 0; index < INVENTORY_SIZE; ++index)
		{
			AMateria *&at = _inventory[index];
			AMateria *otherAt = other._inventory[index];

			if (at)
				delete at;

			at = NULL;

			if (otherAt)
				at = otherAt->clone();
		}
	}

	return (*this);
}

void
Character::zeroInventory()
{
	for (int index = 0; index < INVENTORY_SIZE; ++index)
		_inventory[index] = NULL;
}

const std::string&
Character::getName() const
{
	return (this->_name);
}

void
Character::equip(AMateria *materia)
{
	for (int index = 0; index < INVENTORY_SIZE; ++index)
	{
		AMateria *&at = _inventory[index];

		if (!at)
		{
			at = materia;
			break;
		}
	}
}

void
Character::unequip(int index)
{
	if (index < 0 || index >= INVENTORY_SIZE)
		return;

	_inventory[index] = NULL;
}

void
Character::use(int index, ICharacter &target)
{
	if (index < 0 || index >= INVENTORY_SIZE)
		return;

	AMateria *at = _inventory[index];

	if (at)
		at->use(target);
}
