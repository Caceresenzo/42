/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IncrementDataPointerCommand.hpp                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 16:17:40 by ecaceres          #+#    #+#             */
/*   Updated: 2020/07/15 16:17:40 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INCREMENTDATAPOINTERCOMMAND_HPP_
# define INCREMENTDATAPOINTERCOMMAND_HPP_

#include "../ICommand.hpp"

class IncrementDataPointerCommand : public ICommand
{
	public:
		IncrementDataPointerCommand();
		IncrementDataPointerCommand(size_t position);
		IncrementDataPointerCommand(const IncrementDataPointerCommand &other);

		virtual ~IncrementDataPointerCommand();

		IncrementDataPointerCommand& operator=(const IncrementDataPointerCommand &other);

		virtual void execute(Context &context);

		static ICommand* factory(size_t position);
};

#endif /* INCREMENTDATAPOINTERCOMMAND_HPP_ */
