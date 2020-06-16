/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Human.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 11:32:52 by ecaceres          #+#    #+#             */
/*   Updated: 2020/01/03 11:32:56 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>

#include "Human.hpp"

#define NOTIFY_CALL std::cout << "Called: \e[32m" << __func__ << "\e[39m(\e[33m\"" << target << "\"\e[39m);\e[0m" << std::endl;

void
Human::meleeAttack(std::string const &target)
{
	NOTIFY_CALL;
}

void
Human::rangedAttack(std::string const &target)
{
	NOTIFY_CALL;
}

void
Human::intimidatingShout(std::string const &target)
{
	NOTIFY_CALL;
}

void
Human::action(std::string const &action_name, std::string const &target)
{
	void (Human::*methods[])(std::string const &) = {
		&Human::meleeAttack,
		&Human::rangedAttack,
		&Human::intimidatingShout
	};
	std::string names[] = {
		"melee attack",
		"ranged attack",
		"intimidating shout",
	};

	int count = sizeof(names) / sizeof(std::string);

	for (int index = 0; index < count; index++)
	{
		void (Human::*method)(std::string const &) = methods[index];
		std::string name = names[index];

		if (name == action_name)
		{
			(this->*method)(target);
		}
	}
}
