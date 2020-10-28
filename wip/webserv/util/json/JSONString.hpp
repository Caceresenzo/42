/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JSONString.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 17:42:37 by ecaceres          #+#    #+#             */
/*   Updated: 2020/10/21 17:42:37 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JSONSTRING_HPP_
# define JSONSTRING_HPP_

# include <util/json/JSONBase.hpp>
# include <string>

class JSONString :
		public JSONBase
{
	private:
		std::string m_value;

	public:
		JSONString(void);
		JSONString(std::string value);
		JSONString(const JSONString &other);

		virtual
		~JSONString();

		JSONString&
		operator =(const JSONString &other);

		JSONString&
		operator =(const std::string &other);

		std::string
		toJsonString() const;

		JSONBase*
		clone() const;

		operator std::string(void);
		operator std::string(void) const;

		std::string&
		value(void);

		std::string
		value(void) const;
};

#endif /* JSONSTRING_HPP_ */
