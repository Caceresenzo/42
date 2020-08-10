/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DecrementDataCommand.hpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 16:17:40 by ecaceres          #+#    #+#             */
/*   Updated: 2020/07/15 16:17:40 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DECREMENTDATACOMMAND_HPP_
# define DECREMENTDATACOMMAND_HPP_

#include "../ICommand.hpp"

class DecrementDataCommand : public ICommand
{
	public:
		DecrementDataCommand();
		DecrementDataCommand(size_t position);
		DecrementDataCommand(const DecrementDataCommand &other);

		virtual ~DecrementDataCommand();

		DecrementDataCommand& operator=(const DecrementDataCommand &other);

		virtual void execute(Context &context);

		static ICommand* factory(size_t position);
};

#endif /* DECREMENTDATACOMMAND_HPP_ */
