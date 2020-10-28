/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JSONType.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 18:09:13 by ecaceres          #+#    #+#             */
/*   Updated: 2020/10/21 18:09:13 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JSONTYPE_HPP_
# define JSONTYPE_HPP_

# include <util/json/JSONBase.hpp>
# include <string>

class JSONArray;
class JSONBoolean;
class JSONDouble;
class JSONInteger;
class JSONObject;
class JSONString;
class JSONNull;

class JSONType
{
	private:
		JSONBase *m_ptr;

	public:
		JSONType();
		JSONType(bool value);
		JSONType(int value);
		JSONType(long value);
		JSONType(float value);
		JSONType(double value);
		JSONType(const char *value);
		JSONType(std::string value);
		JSONType(const JSONNull &jsonNull);
		JSONType(const JSONBoolean &jsonBoolean);
		JSONType(const JSONInteger &jsonInteger);
		JSONType(const JSONDouble &jsonDouble);
		JSONType(const JSONString &jsonString);
		JSONType(const JSONArray &jsonArray);
		JSONType(const JSONObject &jsonObject);
		JSONType(const JSONType &other);

		virtual
		~JSONType();

		JSONType&
		operator=(const JSONType &other);

		template<typename T>
			bool
			instanceOf() const
			{
				return (m_ptr->instanceOf<T>());
			}

		std::string
		toJsonString() const;

		operator JSONNull(void) const;
		operator JSONNull&(void);

		operator bool(void) const;
		operator bool(void);
		operator JSONBoolean(void) const;
		operator JSONBoolean&(void);

		operator int(void) const;
		operator int(void);
		operator long(void) const;
		operator long(void);
		operator JSONInteger(void) const;
		operator JSONInteger&(void);

		operator float(void) const;
		operator float(void);
		operator double(void) const;
		operator double(void);
		operator JSONDouble(void) const;
		operator JSONDouble&(void);

		operator std::string(void) const;
		operator std::string&(void);
		operator JSONString(void) const;
		operator JSONString&(void);

		operator JSONArray(void) const;
		operator JSONArray&(void);

		operator JSONObject(void) const;
		operator JSONObject&(void);
};

# include <util/json/JSONArray.hpp>
# include <util/json/JSONBoolean.hpp>
# include <util/json/JSONDouble.hpp>
# include <util/json/JSONInteger.hpp>
# include <util/json/JSONObject.hpp>
# include <util/json/JSONString.hpp>
# include <util/json/JSONNull.hpp>

#endif /* JSONTYPE_HPP_ */
