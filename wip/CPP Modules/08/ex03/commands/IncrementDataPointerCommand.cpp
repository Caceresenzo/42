/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IncrementDataPointerCommand.cpp                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 16:17:40 by ecaceres          #+#    #+#             */
/*   Updated: 2020/07/15 16:17:40 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IncrementDataPointerCommand.hpp"

IncrementDataPointerCommand::IncrementDataPointerCommand() :
		ICommand()
{
}

IncrementDataPointerCommand::IncrementDataPointerCommand(size_t position) :
		ICommand(position)
{
}

IncrementDataPointerCommand::IncrementDataPointerCommand(
        const IncrementDataPointerCommand &other) :
		ICommand(other)
{
	this->operator =(other);
}

IncrementDataPointerCommand::~IncrementDataPointerCommand()
{
}

IncrementDataPointerCommand&
IncrementDataPointerCommand::operator=(const IncrementDataPointerCommand &other)
{
	ICommand::operator =(other);
	return (*this);
}

void
IncrementDataPointerCommand::execute(Context &context)
{
	if (++context.memoryPointer() >= MEMORY_SIZE)
		context.memoryPointer() = 0;
}

ICommand*
IncrementDataPointerCommand::factory(size_t position)
{
	return new IncrementDataPointerCommand(position);
}
