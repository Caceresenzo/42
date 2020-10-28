/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JSONDouble.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 17:42:37 by ecaceres          #+#    #+#             */
/*   Updated: 2020/10/21 17:42:37 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JSONDOUBLE_HPP_
# define JSONDOUBLE_HPP_

# include <util/json/JSONBase.hpp>
# include <util/json/JSONBoolean.hpp>

class JSONDouble :
		public JSONBase
{
	private:
		double m_value;

	public:
		JSONDouble(void);
		JSONDouble(double value);
		JSONDouble(const JSONDouble &other);

		virtual
		~JSONDouble();

		JSONDouble&
		operator =(const JSONDouble &other);

		JSONDouble&
		operator =(const double &other);

		std::string
		toJsonString() const;

		JSONBase*
		clone() const;

		operator double(void);
		operator double(void) const;

		double
		value(void);
};

#endif /* JSONDOUBLE_HPP_ */
