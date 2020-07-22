/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AsteroKreog.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 14:59:32 by ecaceres          #+#    #+#             */
/*   Updated: 2020/07/22 14:59:32 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AsteroKreog.hpp"

AsteroKreog::AsteroKreog()
{
}

AsteroKreog::AsteroKreog(const AsteroKreog &other)
{
	operator =(other);
}

AsteroKreog::~AsteroKreog()
{
}

AsteroKreog&
AsteroKreog::operator=(const AsteroKreog &other)
{
	(void)other;

	return (*this);
}

std::string
AsteroKreog::beMined(DeepCoreMiner*) const
{
	return ("Dragonite");
}

std::string
AsteroKreog::beMined(StripMiner*) const
{
	return ("Flavium");
}

std::string
AsteroKreog::getName() const
{
	return ("kreog");
}
