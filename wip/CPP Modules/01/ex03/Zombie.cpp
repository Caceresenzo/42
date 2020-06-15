/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 11:32:52 by ecaceres          #+#    #+#             */
/*   Updated: 2020/01/03 11:32:56 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>

#include "Zombie.hpp"

Zombie::Zombie(void)
{
	this->_name = "?";
	this->_type = "!";
}

Zombie::Zombie(std::string name, std::string type)
{
	this->_name = name;
	this->_type = type;
}

void
Zombie::setName(std::string name)
{
	this->_name = name;
}

void
Zombie::setType(std::string type)
{
	this->_type = type;
}

void
Zombie::announce(void)
{
	std::cout << "<" << this->_name << " (" << this->_type << ")>";
	std::cout << " Braiiiiiiinnnssss ..." << std::endl;
}
