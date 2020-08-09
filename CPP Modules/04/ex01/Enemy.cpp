/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Enemy.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 17:34:18 by ecaceres          #+#    #+#             */
/*   Updated: 2020/07/21 17:34:18 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Enemy.hpp"

Enemy::Enemy() :
        _hp(0),
        _type("")
{
}

Enemy::Enemy(int hp, std::string type) :
        _hp(hp),
        _type(type)
{
}

Enemy::Enemy(const Enemy &other) :
        _hp(other._hp),
        _type(other._type)
{
	this->operator =(other);
}

Enemy::~Enemy()
{
}

Enemy&
Enemy::operator=(const Enemy &other)
{
	if (this != &other)
	{
		this->_hp = other._hp;
		this->_type = other._type;
	}

	return (*this);
}

void
Enemy::takeDamage(int amount)
{
	if (amount < 0)
		return;

	if ((_hp -= amount) < 0)
		_hp = 0;
}

int
Enemy::getHp() const
{
	return _hp;
}

const std::string&
Enemy::getType() const
{
	return _type;
}
