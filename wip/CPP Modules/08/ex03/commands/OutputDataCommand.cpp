/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OutputDataCommand.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 16:17:40 by ecaceres          #+#    #+#             */
/*   Updated: 2020/07/15 16:17:40 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "OutputDataCommand.hpp"

OutputDataCommand::OutputDataCommand() :
		ICommand()
{
}

OutputDataCommand::OutputDataCommand(size_t position) :
		ICommand(position)
{
}

OutputDataCommand::OutputDataCommand(
        const OutputDataCommand &other) :
		ICommand(other)
{
	this->operator =(other);
}

OutputDataCommand::~OutputDataCommand()
{
}

OutputDataCommand&
OutputDataCommand::operator=(const OutputDataCommand &other)
{
	ICommand::operator =(other);
	return (*this);
}

void
OutputDataCommand::execute(Context &context)
{
	std::cout << context.memory() << std::flush;
}

ICommand*
OutputDataCommand::factory(size_t position)
{
	return new OutputDataCommand(position);
}
