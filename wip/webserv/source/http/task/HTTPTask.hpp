/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HTTPTask.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 19:38:16 by ecaceres          #+#    #+#             */
/*   Updated: 2021/01/10 19:38:16 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPTASK_HPP_
# define HTTPTASK_HPP_

class HTTPTask
{
	public:
		virtual
		~HTTPTask();

		/** @return Whether or not the task is still running. */
		virtual bool
		running() = 0;

		virtual bool
		timeoutTouch(void);
};

#endif /* HTTPTASK_HPP_ */
