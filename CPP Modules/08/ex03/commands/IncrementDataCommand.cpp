/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IncrementDataCommand.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 16:17:40 by ecaceres          #+#    #+#             */
/*   Updated: 2020/07/15 16:17:40 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IncrementDataCommand.hpp"

IncrementDataCommand::IncrementDataCommand() :
		ICommand()
{
}

IncrementDataCommand::IncrementDataCommand(size_t position) :
		ICommand(position)
{
}

IncrementDataCommand::IncrementDataCommand(
        const IncrementDataCommand &other) :
		ICommand(other)
{
	this->operator =(other);
}

IncrementDataCommand::~IncrementDataCommand()
{
}

IncrementDataCommand&
IncrementDataCommand::operator=(const IncrementDataCommand &other)
{
	ICommand::operator =(other);
	return (*this);
}

void
IncrementDataCommand::execute(Context &context)
{
	context.memory()++;
}

ICommand*
IncrementDataCommand::factory(size_t position)
{
	return new IncrementDataCommand(position);
}
