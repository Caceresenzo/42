/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DecrementDataPointerCommand.hpp                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 16:17:40 by ecaceres          #+#    #+#             */
/*   Updated: 2020/07/15 16:17:40 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DECREMENTDATAPOINTERCOMMAND_HPP_
# define DECREMENTDATAPOINTERCOMMAND_HPP_

#include "../ICommand.hpp"

class DecrementDataPointerCommand : public ICommand
{
	public:
		DecrementDataPointerCommand();
		DecrementDataPointerCommand(size_t position);
		DecrementDataPointerCommand(const DecrementDataPointerCommand &other);

		virtual ~DecrementDataPointerCommand();

		DecrementDataPointerCommand& operator=(const DecrementDataPointerCommand &other);

		virtual void execute(Context &context);

		static ICommand* factory(size_t position);
};

#endif /* DECREMENTDATAPOINTERCOMMAND_HPP_ */
