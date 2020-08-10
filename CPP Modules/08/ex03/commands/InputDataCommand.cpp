/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   InputDataCommand.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 16:17:40 by ecaceres          #+#    #+#             */
/*   Updated: 2020/07/15 16:17:40 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "InputDataCommand.hpp"

InputDataCommand::InputDataCommand() :
		ICommand()
{
}

InputDataCommand::InputDataCommand(size_t position) :
		ICommand(position)
{
}

InputDataCommand::InputDataCommand(
        const InputDataCommand &other) :
		ICommand(other)
{
	this->operator =(other);
}

InputDataCommand::~InputDataCommand()
{
}

InputDataCommand&
InputDataCommand::operator=(const InputDataCommand &other)
{
	ICommand::operator =(other);
	return (*this);
}

void
InputDataCommand::execute(Context &context)
{
	std::cin.get(context.memory());
}

ICommand*
InputDataCommand::factory(size_t position)
{
	return new InputDataCommand(position);
}
