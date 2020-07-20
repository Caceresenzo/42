/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DecrementDataCommand.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 16:17:40 by ecaceres          #+#    #+#             */
/*   Updated: 2020/07/15 16:17:40 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DecrementDataCommand.hpp"

DecrementDataCommand::DecrementDataCommand() :
		ICommand()
{
}

DecrementDataCommand::DecrementDataCommand(size_t position) :
		ICommand(position)
{
}

DecrementDataCommand::DecrementDataCommand(
        const DecrementDataCommand &other) :
		ICommand(other)
{
	this->operator =(other);
}

DecrementDataCommand::~DecrementDataCommand()
{
}

DecrementDataCommand&
DecrementDataCommand::operator=(const DecrementDataCommand &other)
{
	ICommand::operator =(other);
	return (*this);
}

void
DecrementDataCommand::execute(Context &context)
{
	context.memory()--;
}

ICommand*
DecrementDataCommand::factory(size_t position)
{
	return new DecrementDataCommand(position);
}
