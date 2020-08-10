/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Context.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 15:53:47 by ecaceres          #+#    #+#             */
/*   Updated: 2020/07/15 15:53:47 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTEXT_HPP_
# define CONTEXT_HPP_

# include <iostream>
# include <vector>
# include <climits>

# define MEMORY_SIZE USHRT_MAX

typedef enum
{
	d_backward = -1, d_forward = 1
} t_pointer_direction;

class ICommand;

class Context
{
	private:
		std::string _source;
		std::vector<ICommand*> _commands;

		long _instructionPointer;
		t_pointer_direction _direction;

		char _memory[MEMORY_SIZE];
		long _memoryPointer;

		int _depth;

	public:
		Context();
		Context(std::string source);
		Context(const Context &other);

		virtual ~Context();

		Context& operator=(const Context &other);

		void zeroMemory();

		void addCommand(ICommand *command);

		ICommand* next();

		long& instructionPointer();
		t_pointer_direction& direction();
		t_pointer_direction inverseDirection();

		char& memory();
		char& memory(long at);
		long& memoryPointer();

		int &depth();

		size_t commandCount();
};

# include "ICommand.hpp"

#endif /* CONTEXT_HPP_ */

