/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandFactory.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 15:58:48 by ecaceres          #+#    #+#             */
/*   Updated: 2020/07/15 15:58:48 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDFACTORY_HPP_
# define COMMANDFACTORY_HPP_

# include <map>

# include "ICommand.hpp"

class CommandFactory
{
	public:
		typedef ICommand *(*Creator)(size_t);

	private:
		std::map<char, Creator> _factories;

		void initialize();
		void registerCreator(char c, Creator creator);

	public:
		CommandFactory();
		CommandFactory(const CommandFactory &other);

		virtual ~CommandFactory();

		CommandFactory& operator=(const CommandFactory &other);

		ICommand *create(char c, size_t position) const;
};

#endif /* COMMANDFACTORY_HPP_ */
