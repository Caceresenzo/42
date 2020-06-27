/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ArrayList.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/04 16:56:11 by ecaceres          #+#    #+#             */
/*   Updated: 2020/01/04 16:56:11 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ArrayList.hpp"

#include <string>
#include <iostream>

#include "Token.hpp"

ArrayList::ArrayList(void)
{
	this->_capacity = 0;
	this->_size = 0;
	this->_array = NULL;

	this->ensureInternalCapacity(10);
}

ArrayList::ArrayList(const std::size_t initialCapacity)
{
	this->_capacity = 0;
	this->_size = 0;
	this->_array = NULL;

	this->ensureInternalCapacity(initialCapacity);
}

ArrayList::ArrayList(const ArrayList &other)
{
	this->operator =(other);
}

ArrayList::~ArrayList(void)
{
	this->deleteArray();
}

ArrayList&
ArrayList::operator =(const ArrayList &other)
{
	if (this != &other)
	{
		this->_capacity = other._capacity;
		this->_size = other._size;

		this->deleteArray();
		this->_array = other.toArray();
	}

	return (*this);
}

void
ArrayList::add(Token *token)
{
	this->ensureInternalCapacity(this->_size);
	this->_array[this->_size++] = token;
}

void
ArrayList::push(Token *token)
{
	this->add(token);
}

void
ArrayList::ensureInternalCapacity(std::size_t of)
{
	if (this->_capacity <= of)
	{
		int required = of + 3;

		Token **nwArray = new Token*[required];

		if (this->_array != NULL)
		{
			std::size_t index;

			for (index = 0; index < this->_size; ++index)
				nwArray[index] = this->_array[index];
			for (; index < of; ++index)
				nwArray[index] = NULL;
		}

		delete[] this->_array;
		this->_array = nwArray;

		this->_capacity = required;
	}
}

void
ArrayList::deleteArray(void)
{
	if (this->_array != NULL)
	{
		Token *token = NULL;

		do
			delete (token = this->pop());
		while (token != NULL);
	}

	delete[] this->_array;
}

Token*
ArrayList::unsafeGet(std::size_t index) const
{
	return (this->_array[index]);
}

Token*
ArrayList::get(std::size_t index) const
{
	if (index >= this->_size)
		return (NULL);

	return (this->unsafeGet(index));
}

Token*
ArrayList::first(void) const
{
	if (this->_size == 0)
		return (NULL);

	return (this->unsafeGet(0));
}

Token*
ArrayList::peek(void) const
{
	if (this->_size == 0)
		return (NULL);

	return (this->unsafeGet(this->_size - 1));
}

Token*
ArrayList::remove(std::size_t index)
{
	if (this->_size == 0 || index >= this->size())
		return (NULL);

	Token *ptr = this->_array[index];

	for (; index < this->_size; ++index)
		this->_array[index] = this->_array[index + 1];

	if (index < this->_capacity)
		this->_array[index] = NULL;

	this->_size--;

	return (ptr);
}

Token*
ArrayList::pop(void)
{
	return (this->remove(this->size() - 1));
}

std::size_t
ArrayList::indexOf(Token *token) const
{
	for (std::size_t index = 0; index < this->_size; index++)
	{
		if (this->_array[index] == token)
			return (index);
	}

	return (std::string::npos);
}

std::size_t
ArrayList::size(void) const
{
	return (this->_size);
}

bool
ArrayList::empty(void) const
{
	return (this->_size == 0);
}

Token**
ArrayList::toArray(void) const
{
	Token **array = new Token*[this->_size + 1];

	std::size_t index;
	for (index = 0; index < this->_size; index++)
		array[index] = this->_array[index];
	array[index] = NULL;

	return (array);
}
