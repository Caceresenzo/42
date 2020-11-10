/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JSONNull.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 17:38:07 by ecaceres          #+#    #+#             */
/*   Updated: 2020/10/21 17:38:07 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JSONNULL_HPP_
# define JSONNULL_HPP_

#include <util/json/JSONBase.hpp>

class JSONNull :
		public JSONBase
{
	public:
		JSONNull(void);
		JSONNull(const JSONNull &other);

		virtual
		~JSONNull();

		JSONNull&
		operator =(const JSONNull &other);

		std::string
		toJsonString() const;

		JSONBase*
		clone() const;
};

#endif /* JSONNULL_HPP_ */
