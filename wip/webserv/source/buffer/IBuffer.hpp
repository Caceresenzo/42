/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IBuffer.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 18:19:03 by ecaceres          #+#    #+#             */
/*   Updated: 2020/11/29 18:19:03 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IBUFFER_HPP_
# define IBUFFER_HPP_

#include <string>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

class IBuffer
{
	public:
		virtual
		~IBuffer(void);

		/** @return Buffer storage. */
		virtual std::string&
		storage(void) = 0;

		/** @return Buffer constant storage. */
		virtual const std::string&
		storage(void) const = 0;
};

#endif /* IBUFFER_HPP_ */
