/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Squad.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 19:16:02 by ecaceres          #+#    #+#             */
/*   Updated: 2020/07/21 19:16:02 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Squad.hpp"

#include <iostream>
#include <string>

#include "ISpaceMarine.hpp"

Squad::Squad() :
        _size(0),
        _array(NULL)
{
}

Squad::Squad(const Squad &other) :
        _size(0),
        _array(NULL)
{
	this->operator =(other);
}

Squad::~Squad()
{
	if (this->_array)
	{
		for (int index = 0; index < this->_size; ++index)
		{

			ISpaceMarine *&marine = this->_array[index];

			delete marine;
			marine = NULL;
		}

		delete[] this->_array;
		this->_array = NULL;
	}
}

Squad&
Squad::operator=(const Squad &other)
{
	if (this != &other)
	{
		int index;

		/* Copy from other. */
		for (index = 0; index < other._size; ++index)
		{
			if (index >= this->_size)
				break;

			ISpaceMarine *&marine = this->_array[index];

			delete marine;

			marine = other._array[index]->clone();
		}

		/* Add missing from other. */
		for (; index < other._size; ++index)
			push(other._array[index]->clone());

		/* Clear if original was too large. */
		for (; index < this->_size; ++index)
		{
			ISpaceMarine *&marine = this->_array[index];

			delete marine;

			marine = NULL;
		}

		this->_size = other._size;
	}

	return (*this);
}

int
Squad::getCount() const
{
	return (this->_size);
}

ISpaceMarine*
Squad::getUnit(int index) const
{
	if (index < 0 || index >= this->_size)
		return (NULL); /* Out of bounds */

	return (this->_array[index]);
}

int
Squad::push(ISpaceMarine *marine)
{
	if (!marine)
		return (0);

	ISpaceMarine **newArray = new ISpaceMarine*[this->_size + 1];

	int index;
	for (index = 0; index < this->_size; ++index)
		newArray[index] = this->_array[index];

	newArray[index] = marine;

	delete[] this->_array;
	this->_array = newArray;

	return (++this->_size);
}
