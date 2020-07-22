/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MiningBarge.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 15:07:39 by ecaceres          #+#    #+#             */
/*   Updated: 2020/07/22 15:07:39 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MiningBarge.hpp"

MiningBarge::MiningBarge()
{
	zeroInventory();
}

MiningBarge::MiningBarge(const MiningBarge &other)
{
	zeroInventory();

	operator =(other);
}

MiningBarge::~MiningBarge()
{
}

MiningBarge&
MiningBarge::operator=(const MiningBarge &other)
{
	if (this != &other)
	{
		for (int index = 0; index < INVENTORY_SIZE; ++index)
			_inventory[index] = other._inventory[index];
	}

	return (*this);
}

void
MiningBarge::zeroInventory()
{
	for (int index = 0; index < INVENTORY_SIZE; ++index)
		_inventory[index] = NULL;
}

void
MiningBarge::equip(IMiningLaser *laser)
{
	for (int index = 0; index < INVENTORY_SIZE; ++index)
	{
		IMiningLaser *&at = _inventory[index];

		if (!at)
		{
			at = laser;
			break;
		}
	}
}

void
MiningBarge::mine(IAsteroid *asteroid) const
{
	for (int index = 0; index < INVENTORY_SIZE; ++index)
	{
		IMiningLaser *at = _inventory[index];

		if (!at)
			break;

		at->mine(asteroid);
	}
}
