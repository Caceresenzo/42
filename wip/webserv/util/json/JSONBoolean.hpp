/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JSONBoolean.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 17:38:52 by ecaceres          #+#    #+#             */
/*   Updated: 2020/10/21 17:38:52 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JSONBOOLEAN_HPP_
# define JSONBOOLEAN_HPP_

#include <util/json/JSONBase.hpp>

class JSONBoolean :
		public JSONBase
{
	private:
		bool m_value;

	public:
		JSONBoolean(void);
		JSONBoolean(bool value);
		JSONBoolean(const JSONBoolean &other);

		virtual
		~JSONBoolean(void);

		JSONBoolean&
		operator =(const JSONBoolean &other);

		JSONBoolean&
		operator =(const bool &other);

		std::string
		toJsonString() const;

		JSONBase*
		clone() const;

		operator bool(void);
		operator bool(void) const;

		bool
		value(void);
};

#endif /* JSONBOOLEAN_HPP_ */
