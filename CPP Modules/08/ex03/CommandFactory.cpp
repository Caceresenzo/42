/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandFactory.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 15:58:48 by ecaceres          #+#    #+#             */
/*   Updated: 2020/07/15 15:58:48 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CommandFactory.hpp"
#include "Mindopen.hpp"

#include <cstddef>
#include <utility>

#include "commands/DecrementDataCommand.hpp"
#include "commands/DecrementDataPointerCommand.hpp"
#include "commands/IncrementDataCommand.hpp"
#include "commands/IncrementDataPointerCommand.hpp"
#include "commands/InputDataCommand.hpp"
#include "commands/OutputDataCommand.hpp"
#include "commands/WhileCloseCommand.hpp"
#include "commands/WhileOpenCommand.hpp"

CommandFactory::CommandFactory()
{
	initialize();
}

CommandFactory::CommandFactory(const CommandFactory &other)
{
	this->operator =(other);
}

CommandFactory::~CommandFactory()
{
}

CommandFactory&
CommandFactory::operator=(const CommandFactory &other)
{
	if (this != &other)
	{
		this->_factories = other._factories;
	}

	return (*this);
}

void
CommandFactory::initialize()
{
	registerCreator(MO_INCREMENT_DATA, IncrementDataPointerCommand::factory);
	registerCreator(MO_DECREMENT_DATA, DecrementDataPointerCommand::factory);
	registerCreator(MO_INCREMENT, IncrementDataCommand::factory);
	registerCreator(MO_DECREMENT, DecrementDataCommand::factory);
	registerCreator(MO_OUTPUT, OutputDataCommand::factory);
	registerCreator(MO_INPUT, InputDataCommand::factory);
	registerCreator(MO_WHILE_OPEN, WhileOpenCommand::factory);
	registerCreator(MO_WHILE_CLOSE, WhileCloseCommand::factory);
}

void
CommandFactory::registerCreator(char c, Creator creator)
{
	this->_factories.insert(std::make_pair(c, creator));
}

ICommand*
CommandFactory::create(char c, size_t position) const
{
	std::map<char, Creator>::const_iterator it = this->_factories.find(c);

	if (it != this->_factories.end())
	{
		Creator creator = (*it).second;

		if (creator != NULL)
			return ((*creator)(position));
	}

	return (NULL);
}
