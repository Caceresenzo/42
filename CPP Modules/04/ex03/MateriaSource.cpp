/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MateriaSource.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 11:59:49 by ecaceres          #+#    #+#             */
/*   Updated: 2020/07/22 11:59:49 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MateriaSource.hpp"

MateriaSource::MateriaSource()
{
	zeroInventory();
}

MateriaSource::MateriaSource(const MateriaSource &other)
{
	zeroInventory();

	this->operator =(other);
}

MateriaSource::~MateriaSource()
{
	for (int index = 0; index < INVENTORY_SIZE; ++index)
	{
		AMateria *&at = _inventory[index];

		if (at)
			delete at;

		at = NULL;
	}
}

MateriaSource&
MateriaSource::operator=(const MateriaSource &other)
{
	if (this != &other)
	{
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
MateriaSource::zeroInventory()
{
	for (int index = 0; index < INVENTORY_SIZE; ++index)
		_inventory[index] = NULL;
}

void
MateriaSource::learnMateria(AMateria *materia)
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

AMateria*
MateriaSource::createMateria(const std::string &type)
{
	for (int index = 0; index < INVENTORY_SIZE; ++index)
	{
		AMateria *at = _inventory[index];

		if (at && at->getType() == type)
			return (at->clone());
	}

	return (NULL);
}
