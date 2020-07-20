/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WhileOpenCommand.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 16:17:40 by ecaceres          #+#    #+#             */
/*   Updated: 2020/07/15 16:17:40 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WHILEOPENCOMMAND_HPP_
# define WHILEOPENCOMMAND_HPP_

#include "../ICommand.hpp"

class WhileOpenCommand : public ICommand
{
	public:
		WhileOpenCommand();
		WhileOpenCommand(size_t position);
		WhileOpenCommand(const WhileOpenCommand &other);

		virtual ~WhileOpenCommand();

		WhileOpenCommand& operator=(const WhileOpenCommand &other);

		virtual void execute(Context &context);

		static ICommand* factory(size_t position);
};

#endif /* WHILEOPENCOMMAND_HPP_ */
