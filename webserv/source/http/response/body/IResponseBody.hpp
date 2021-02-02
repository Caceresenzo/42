/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IResponseBody.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atetu <atetu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 17:08:17 by ecaceres          #+#    #+#             */
/*   Updated: 2021/01/27 10:22:23 by atetu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRESPONSEBODY_HPP_
# define IRESPONSEBODY_HPP_

#include <buffer/impl/BaseBuffer.hpp>

class FileDescriptorBuffer;

class IResponseBody
{
	public:
		virtual
		~IResponseBody();

		virtual bool
		store(BaseBuffer &buffer) = 0;

		virtual bool
		isSelfManaged() const;
};

#endif /* IRESPONSEBODY_HPP_ */
