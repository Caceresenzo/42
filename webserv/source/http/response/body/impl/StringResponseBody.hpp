/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StringResponseBody.hpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atetu <atetu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 17:10:52 by ecaceres          #+#    #+#             */
/*   Updated: 2021/01/27 10:26:12 by atetu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRINGRESPONSEBODY_HPP_
# define STRINGRESPONSEBODY_HPP_

#include <http/response/body/IResponseBody.hpp>

class StringResponseBody :
		public IResponseBody
{
	private:
		std::string m_content;

	public:
		StringResponseBody();
		StringResponseBody(const std::string &content);
		StringResponseBody(const StringResponseBody &other);

		virtual
		~StringResponseBody();

		StringResponseBody&
		operator=(const StringResponseBody &other);

		bool
		store(BaseBuffer &buffer);
};

#endif /* STRINGRESPONSEBODY_HPP_ */
