/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StripMiner.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 14:50:47 by ecaceres          #+#    #+#             */
/*   Updated: 2020/07/22 14:50:47 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "StripMiner.hpp"

#include <iostream>

StripMiner::StripMiner()
{
}

StripMiner::StripMiner(const StripMiner &other)
{
	this->operator =(other);
}

StripMiner::~StripMiner()
{
}

StripMiner&
StripMiner::operator=(const StripMiner &other)
{
	(void)other;

	return (*this);
}

void
StripMiner::mine(IAsteroid *asteroid)
{
	std::cout << "* strip mining ... got " << asteroid->beMined(this) << " ! *" << std::endl;
}
