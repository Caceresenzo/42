/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DeepCoreMiner.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 14:50:47 by ecaceres          #+#    #+#             */
/*   Updated: 2020/07/22 14:50:47 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DeepCoreMiner.hpp"

#include <iostream>

DeepCoreMiner::DeepCoreMiner()
{
}

DeepCoreMiner::DeepCoreMiner(const DeepCoreMiner &other)
{
	this->operator =(other);
}

DeepCoreMiner::~DeepCoreMiner()
{
}

DeepCoreMiner&
DeepCoreMiner::operator=(const DeepCoreMiner &other)
{
	(void)other;

	return (*this);
}

void
DeepCoreMiner::mine(IAsteroid *asteroid)
{
	std::cout << "* mining deep ... got " << asteroid->beMined(this) << " ! *" << std::endl;
}
