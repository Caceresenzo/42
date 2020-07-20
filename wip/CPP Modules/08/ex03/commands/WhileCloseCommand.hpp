/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WhileCloseCommand.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 16:17:40 by ecaceres          #+#    #+#             */
/*   Updated: 2020/07/15 16:17:40 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WHILECLOSECOMMAND_HPP_
# define WHILECLOSECOMMAND_HPP_

#include "../ICommand.hpp"

class WhileCloseCommand : public ICommand
{
	public:
		WhileCloseCommand();
		WhileCloseCommand(size_t position);
		WhileCloseCommand(const WhileCloseCommand &other);

		virtual ~WhileCloseCommand();

		WhileCloseCommand& operator=(const WhileCloseCommand &other);

		virtual void execute(Context &context);

		static ICommand* factory(size_t position);
};

#endif /* WHILECLOSECOMMAND_HPP_ */
