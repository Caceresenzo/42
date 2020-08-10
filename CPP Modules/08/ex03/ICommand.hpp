/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ICommand.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 15:52:17 by ecaceres          #+#    #+#             */
/*   Updated: 2020/07/15 15:52:17 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ICOMMAND_HPP_
# define ICOMMAND_HPP_

# include <cstddef>
# include <exception>
# include <iostream>

class Context;

class ICommand
{
	private:
		size_t _position;

	protected:
		ICommand();
		ICommand(size_t position);
		ICommand(const ICommand &other);

	public:
		virtual ~ICommand();

		ICommand& operator=(const ICommand &other);

		virtual void execute(Context &context);

		size_t position() const;

		class CommandException : public std::exception
		{
			private:
				const ICommand *_command;
				const std::string _message;

			public:
				CommandException(void);
				CommandException(ICommand *command);
				CommandException(ICommand *command, std::string message);
				CommandException(const CommandException &other);

				virtual ~CommandException(void) throw ();

				CommandException& operator=(const CommandException &other);

				virtual const char* what() const throw ();

				const std::string &message() const;
				const ICommand *command() const;

				static CommandException generic(ICommand *command, std::string reason);
				static CommandException notImplemented(ICommand *command);
		};
};

# include "Context.hpp"

#endif /* ICOMMAND_HPP_ */
