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

#include "Fixed.hpp"

#include <cmath>

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

bool
Fixed::operator >(const Fixed &right) const
{
	return (getRawBits() > right.getRawBits());
}

bool
Fixed::operator <(const Fixed &right) const
{
	return (getRawBits() < right.getRawBits());
}

bool
Fixed::operator >=(const Fixed &right) const
{
	return (getRawBits() >= right.getRawBits());
}

bool
Fixed::operator <=(const Fixed &right) const
{
	return (getRawBits() <= right.getRawBits());
}

bool
Fixed::operator ==(const Fixed &right) const
{
	return (getRawBits() == right.getRawBits());
}

bool
Fixed::operator !=(const Fixed &right) const
{
	return (getRawBits() != right.getRawBits());
}

Fixed
Fixed::operator +(const Fixed &right) const
{
	Fixed fixed;

	fixed.setRawBits(getRawBits() + right.getRawBits());

	return (fixed);
}

Fixed
Fixed::operator -(const Fixed &right) const
{
	Fixed fixed;

	fixed.setRawBits(getRawBits() - right.getRawBits());

	return (fixed);
}

Fixed
Fixed::operator *(const Fixed &right) const
{
	return (Fixed(toFloat() * right.toFloat()));
}

Fixed
Fixed::operator /(const Fixed &right) const
{
	return (Fixed(toFloat() / right.toFloat()));
}

Fixed&
Fixed::operator ++(void)
{
	this->_value += 1;
	return (*this);
}

Fixed&
Fixed::operator --(void)
{
	this->_value -= 1;
	return (*this);
}

Fixed
Fixed::operator ++(int)
{
	Fixed cpy(*this);

	operator ++();

	return (cpy);
}

Fixed
Fixed::operator --(int)
{
	Fixed cpy(*this);

	operator --();

	return (cpy);
}

std::ostream&
operator <<(std::ostream &stream, const Fixed &fixed)
{
	return (stream << fixed.toFloat());
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

Fixed&
Fixed::min(Fixed &a, Fixed &b)
{
	return (a < b ? a : b);
}

const Fixed&
Fixed::min(const Fixed &a, const Fixed &b)
{
	return (a < b ? a : b);
}

Fixed&
Fixed::max(Fixed &a, Fixed &b)
{
	return (a > b ? a : b);
}

const Fixed&
Fixed::max(const Fixed &a, const Fixed &b)
{
	return (a > b ? a : b);
}
