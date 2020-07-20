/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DecrementDataPointerCommand.cpp                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 16:17:40 by ecaceres          #+#    #+#             */
/*   Updated: 2020/07/15 16:17:40 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DecrementDataPointerCommand.hpp"

DecrementDataPointerCommand::DecrementDataPointerCommand() :
		ICommand()
{
}

DecrementDataPointerCommand::DecrementDataPointerCommand(size_t position) :
		ICommand(position)
{
}

DecrementDataPointerCommand::DecrementDataPointerCommand(
        const DecrementDataPointerCommand &other) :
		ICommand(other)
{
	this->operator =(other);
}

DecrementDataPointerCommand::~DecrementDataPointerCommand()
{
}

DecrementDataPointerCommand&
DecrementDataPointerCommand::operator=(const DecrementDataPointerCommand &other)
{
	ICommand::operator =(other);
	return (*this);
}

void
DecrementDataPointerCommand::execute(Context &context)
{
	if (--context.memoryPointer() < 0)
		context.memoryPointer() = MEMORY_SIZE - 1;
}

ICommand*
DecrementDataPointerCommand::factory(size_t position)
{
	return new DecrementDataPointerCommand(position);
}
