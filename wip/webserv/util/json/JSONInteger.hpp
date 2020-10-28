/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JSONInteger.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 17:42:37 by ecaceres          #+#    #+#             */
/*   Updated: 2020/10/21 17:42:37 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JSONINTEGER_HPP_
# define JSONINTEGER_HPP_

# include <util/json/JSONBase.hpp>

class JSONInteger :
		public JSONBase
{
	private:
		long m_value;

	public:
		JSONInteger();
		JSONInteger(long value);
		JSONInteger(const JSONInteger &other);

		virtual
		~JSONInteger();

		JSONInteger&
		operator =(const JSONInteger &other);

		JSONInteger&
		operator =(const long &other);

		std::string
		toJsonString() const;

		JSONBase*
		clone() const;

		operator long(void);
		operator long(void) const;

		long
		value(void);
};

#endif /* JSONINTEGER_HPP_ */
