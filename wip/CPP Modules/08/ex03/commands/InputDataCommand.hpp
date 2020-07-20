/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   InputDataCommand.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 16:17:40 by ecaceres          #+#    #+#             */
/*   Updated: 2020/07/15 16:17:40 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUTDATACOMMAND_HPP_
# define INPUTDATACOMMAND_HPP_

#include "../ICommand.hpp"

class InputDataCommand : public ICommand
{
	public:
		InputDataCommand();
		InputDataCommand(size_t position);
		InputDataCommand(const InputDataCommand &other);

		virtual ~InputDataCommand();

		InputDataCommand& operator=(const InputDataCommand &other);

		virtual void execute(Context &context);

		static ICommand* factory(size_t position);
};

#endif /* INPUTDATACOMMAND_HPP_ */
