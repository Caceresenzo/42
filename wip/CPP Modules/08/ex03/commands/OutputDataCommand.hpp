/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OutputDataCommand.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 16:17:40 by ecaceres          #+#    #+#             */
/*   Updated: 2020/07/15 16:17:40 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OUTPUTDATACOMMAND_HPP_
# define OUTPUTDATACOMMAND_HPP_

#include "../ICommand.hpp"

class OutputDataCommand : public ICommand
{
	public:
		OutputDataCommand();
		OutputDataCommand(size_t position);
		OutputDataCommand(const OutputDataCommand &other);

		virtual ~OutputDataCommand();

		OutputDataCommand& operator=(const OutputDataCommand &other);

		virtual void execute(Context &context);

		static ICommand* factory(size_t position);
};

#endif /* OUTPUTDATACOMMAND_HPP_ */
