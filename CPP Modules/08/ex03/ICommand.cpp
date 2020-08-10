/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ICommand.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 15:52:17 by ecaceres          #+#    #+#             */
/*   Updated: 2020/07/15 15:52:17 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <exception>
#include <iostream>

#include "ICommand.hpp"

ICommand::ICommand() :
		_position(std::string::npos)
{
}

ICommand::ICommand(size_t position) :
		_position(position)
{
}

ICommand::ICommand(const ICommand &other) :
		_position(other._position)
{
	this->operator =(other);
}

ICommand::~ICommand()
{
}

ICommand&
ICommand::operator=(const ICommand &other)
{
	(void)other;

	return (*this);
}

void
ICommand::execute(Context &context)
{
	(void)context;

	throw CommandException::notImplemented(this);
}

size_t
ICommand::position() const
{
	return (this->_position);
}

ICommand::CommandException::CommandException(void) :
		std::exception(), _command(NULL), _message("no message")
{
}

ICommand::CommandException::CommandException(ICommand *command) :
		std::exception(), _command(command), _message("no message")
{
}

ICommand::CommandException::CommandException(ICommand *command, std::string message) :
		std::exception(), _command(command), _message(message)
{
}

ICommand::CommandException::CommandException(const CommandException &other) :
		std::exception(), _command(other._command), _message(other._message)
{
}

ICommand::CommandException::~CommandException(void) throw ()
{
}

ICommand::CommandException&
ICommand::CommandException::operator =(const CommandException &other)
{
	(void)other;

	return (*this);
}

const char*
ICommand::CommandException::what() const throw ()
{
	return (this->_message.c_str());
}

const std::string&
ICommand::CommandException::message() const
{
	return (this->_message);
}

const ICommand*
ICommand::CommandException::command() const
{
	return (this->_command);
}

ICommand::CommandException
ICommand::CommandException::generic(ICommand *command, std::string reason)
{
	return (CommandException(command, reason));
}

ICommand::CommandException
ICommand::CommandException::notImplemented(ICommand *command)
{
	return (CommandException(command, "not implemented"));
}
