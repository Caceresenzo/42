/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Sorcerer.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 12:18:41 by ecaceres          #+#    #+#             */
/*   Updated: 2020/07/21 12:18:41 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Sorcerer.hpp"

Sorcerer::Sorcerer()
{
}

Sorcerer::Sorcerer(std::string name, std::string title) :
        _name(name),
        _title(title)
{
	std::cout << _name << ", " << _title << ", is born!" << std::endl;
}

Sorcerer::Sorcerer(const Sorcerer &other) :
        _name(other._name),
        _title(other._title)
{
	std::cout << _name << ", " << _title << ", is born!" << std::endl;
}

Sorcerer::~Sorcerer()
{
	std::cout << _name << ", " << _title << ", is dead. Consequences will never be the same!" << std::endl;
}

Sorcerer&
Sorcerer::operator=(const Sorcerer &other)
{
	if (this != &other)
	{
		this->_name = other._name;
		this->_title = other._title;
	}

	return (*this);
}

const std::string&
Sorcerer::getName() const
{
	return _name;
}

void
Sorcerer::polymorph(const Victim &victim) const
{
	victim.getPolymorphed();
}

const std::string&
Sorcerer::getTitle() const
{
	return _title;
}

std::ostream&
operator <<(std::ostream &stream, Sorcerer &sorcerer)
{
	return (stream << "I am " << sorcerer.getName() << ", " << sorcerer.getTitle() << ", and i like ponies!" << std::endl);
}
