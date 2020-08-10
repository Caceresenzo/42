/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IncrementDataCommand.hpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 16:17:40 by ecaceres          #+#    #+#             */
/*   Updated: 2020/07/15 16:17:40 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INCREMENTDATACOMMAND_HPP_
# define INCREMENTDATACOMMAND_HPP_

#include "../ICommand.hpp"

class IncrementDataCommand : public ICommand
{
	public:
		IncrementDataCommand();
		IncrementDataCommand(size_t position);
		IncrementDataCommand(const IncrementDataCommand &other);

		virtual ~IncrementDataCommand();

		IncrementDataCommand& operator=(const IncrementDataCommand &other);

		virtual void execute(Context &context);

		static ICommand* factory(size_t position);
};

#endif /* INCREMENTDATACOMMAND_HPP_ */
