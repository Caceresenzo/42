/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pony.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 11:32:52 by ecaceres          #+#    #+#             */
/*   Updated: 2020/01/03 11:32:56 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>

#include "Pony.hpp"

Pony::Pony(std::string name, t_color color)
{
	this->name = name.size() == 0 ? "Unnammed" : name;
	this->color = color;
}

Pony::~Pony(void)
{
	this->name = "";
	this->color = c_nocolor;

	std::cout << "\e[91mDestructor called.\e[0m" << std::endl;
}

void
Pony::tellName(void)
{
	std::cout << "My name is: " << this->name << std::endl;
}

void
Pony::changeColor(t_color newColor)
{
	this->color = newColor;
}

void
Pony::tellColor(void)
{
	std::string color;

	switch (this->color)
	{
		case c_nocolor: {
			color = "Nothing";
			break ;
		}

		case c_white: {
			color = "White";
			break ;
		}

		case c_brown: {
			color = "Brown";
			break ;
		}

		case c_black: {
			color = "Black";
			break ;
		}

		default: {
			color = "Unknown";
			break ;
		}
	}

	std::cout << "My color is: " << color << std::endl;
}
