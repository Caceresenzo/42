/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Context.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 15:53:47 by ecaceres          #+#    #+#             */
/*   Updated: 2020/07/15 15:53:47 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Context.hpp"

Context::Context() :
        _source(""),
        _instructionPointer(-1),
        _direction(d_forward),
        _memoryPointer(0),
        _depth(0)
{
	zeroMemory();
}

Context::Context(std::string source) :
        _source(source),
        _instructionPointer(-1),
        _direction(d_forward),
        _memoryPointer(0),
        _depth(0)
{
	zeroMemory();
}

Context::Context(const Context &other) :
        _source(other._source),
        _instructionPointer(other._instructionPointer),
        _direction(other._direction),
        _memoryPointer(other._memoryPointer),
        _depth(other._depth)
{
	this->operator =(other);
}

Context::~Context()
{
	size_t total = this->_commands.size();

	for (size_t index = 0; index < total; ++index)
		delete _commands[index];

	this->_commands.clear();
}

Context&
Context::operator=(const Context &other)
{
	if (this != &other)
	{
		this->_source = other._source;
		this->_commands = other._commands;

		this->_instructionPointer = other._instructionPointer;
		this->_direction = other._direction;

		for (int index = 0; index < MEMORY_SIZE; ++index)
			this->_memory[index] = other._memory[index];

		this->_memoryPointer = other._memoryPointer;

		this->_depth = other._depth;
	}
	return (*this);
}

void
Context::zeroMemory()
{
	for (int index = 0; index < MEMORY_SIZE; ++index)
		_memory[index] = 0;
}

void
Context::addCommand(ICommand *command)
{
	this->_commands.push_back(command);
}

ICommand*
Context::next()
{
	size_t to = _instructionPointer + _direction;

	if (to < 0 || to >= _commands.size())
		return (NULL);

	return (_commands[_instructionPointer = to]);
}

long&
Context::instructionPointer()
{
	return (this->_instructionPointer);
}

t_pointer_direction&
Context::direction()
{
	return (this->_direction);
}

t_pointer_direction
Context::inverseDirection()
{
	return (_direction = _direction == d_forward ? d_backward : d_forward);
}

char&
Context::memory()
{
	return (this->memory(this->_memoryPointer));
}

char&
Context::memory(long at)
{
	return (this->_memory[at]);
}

long&
Context::memoryPointer()
{
	return (this->_memoryPointer);
}

int&
Context::depth()
{
	return (this->_depth);
}

size_t
Context::commandCount()
{
	return (this->_commands.size());
}
