/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/04 16:56:11 by ecaceres          #+#    #+#             */
/*   Updated: 2020/01/04 16:56:11 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <cmath>

#include "Fixed.hpp"

const int Fixed::_BIT_COUNT = 8;

Fixed::Fixed(void)
{
	this->_value = 0;
}

Fixed::Fixed(const int value)
{
	this->_value = value << _BIT_COUNT;
}

Fixed::Fixed(const float value)
{
	this->_value = roundf(value * (1 << _BIT_COUNT));
}

Fixed::Fixed(const Fixed &other)
{
	*this = other;
}

Fixed::~Fixed(void)
{
	this->_value = 0;
}

Fixed&
Fixed::operator =(const Fixed &other)
{
	if (this != &other)
	{
		this->_value = other.getRawBits();
	}

	return (*this);
}

int
Fixed::getRawBits(void) const
{
	return (this->_value);
}

void
Fixed::setRawBits(int const raw)
{
	this->_value = raw;
}

int
Fixed::toInt(void) const
{
	return (this->_value >> _BIT_COUNT);
}

float
Fixed::toFloat(void) const
{
	return (((float)this->_value) / (1 << _BIT_COUNT));
}

std::ostream&
operator <<(std::ostream &stream, const Fixed &fixed)
{
	return (stream << fixed.toFloat());
}
