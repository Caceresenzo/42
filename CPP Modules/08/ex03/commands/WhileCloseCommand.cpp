/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WhileCloseCommand.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 16:17:40 by ecaceres          #+#    #+#             */
/*   Updated: 2020/07/15 16:17:40 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WhileCloseCommand.hpp"
#include "WhileOpenCommand.hpp"

WhileCloseCommand::WhileCloseCommand() :
		ICommand()
{
}

WhileCloseCommand::WhileCloseCommand(size_t position) :
		ICommand(position)
{
}

WhileCloseCommand::WhileCloseCommand(
        const WhileCloseCommand &other) :
		ICommand(other)
{
	this->operator =(other);
}

WhileCloseCommand::~WhileCloseCommand()
{
}

WhileCloseCommand&
WhileCloseCommand::operator=(const WhileCloseCommand &other)
{
	ICommand::operator =(other);
	return (*this);
}

void
WhileCloseCommand::execute(Context &context)
{
	if (context.memory() != 0)
	{
		context.inverseDirection();

		ICommand *next = context.next();
		while (context.depth() > 0 || !dynamic_cast<WhileOpenCommand*>(next))
		{
			if (dynamic_cast<WhileCloseCommand*>(next))
				context.depth()++;

			if (dynamic_cast<WhileOpenCommand*>(next))
				context.depth()--;

			next = context.next();
		}

		next = context.next();
		context.inverseDirection();
	}
}

ICommand*
WhileCloseCommand::factory(size_t position)
{
	return new WhileCloseCommand(position);
}
