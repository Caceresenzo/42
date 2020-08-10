/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WhileOpenCommand.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 16:17:40 by ecaceres          #+#    #+#             */
/*   Updated: 2020/07/15 16:17:40 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WhileOpenCommand.hpp"
#include "WhileCloseCommand.hpp"

WhileOpenCommand::WhileOpenCommand() :
		ICommand()
{
}

WhileOpenCommand::WhileOpenCommand(size_t position) :
		ICommand(position)
{
}

WhileOpenCommand::WhileOpenCommand(
        const WhileOpenCommand &other) :
		ICommand(other)
{
	this->operator =(other);
}

WhileOpenCommand::~WhileOpenCommand()
{
}

WhileOpenCommand&
WhileOpenCommand::operator=(const WhileOpenCommand &other)
{
	ICommand::operator =(other);
	return (*this);
}

void
WhileOpenCommand::execute(Context &context)
{
	if (context.memory() == 0)
	{
		ICommand *next = context.next();
		while (context.depth() > 0 || !dynamic_cast<WhileCloseCommand*>(next))
		{
			if (dynamic_cast<WhileOpenCommand*>(next))
				context.depth()++;

			if (dynamic_cast<WhileCloseCommand*>(next))
				context.depth()--;

			next = context.next();
		}
	}
}

ICommand*
WhileOpenCommand::factory(size_t position)
{
	return new WhileOpenCommand(position);
}
