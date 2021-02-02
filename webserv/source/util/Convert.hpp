/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Convert.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 19:04:49 by ecaceres          #+#    #+#             */
/*   Updated: 2020/10/27 19:04:49 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONVERT_HPP_
# define CONVERT_HPP_

#include <util/Object.hpp>
#include <util/TypeTraits.hpp>
#include <iomanip>
#include <sstream>
#include <string>

class Convert
{
	public:
		template<typename T>
			inline static std::string
			toString(const T &t, typename enable_if<!is_pointer<T>::value>::type* = 0)
			{
				std::stringstream stream;

				stream << t;

				return (stream.str());
			}

		template<typename T>
			inline static std::string
			toString(const T &t, typename enable_if<is_pointer<T>::value>::type* = 0)
			{
				std::stringstream stream;

				stream << *t; /* Reimpl to avoid deep pointer. */

				return (stream.str());
			}

		template<typename T>
			inline static std::string
			toString(const T &t, int base)
			{
				std::stringstream stream;

				stream << std::setbase(base) << t;

				return (stream.str());
			}

		template<typename Container>
			inline static std::string
			join(const Container container)
			{
				return (join<Container>(container, ", ", "", ""));
			}

		template<typename Container>
			inline static std::string
			join(const Container container, const std::string &separator)
			{
				return (join<Container>(container, separator, "", ""));
			}

		template<typename Container>
			inline static std::string
			join(const Container container, const std::string &separator, const std::string &prefix, const std::string &suffix)
			{
				typedef typename Container::const_iterator iterator;

				iterator it = container.begin();
				iterator ite = container.end();

				std::string out(prefix);
				while (it != ite)
				{
					out += toString(*it);

					if (++it != ite)
						out += separator;
				}

				return (out += suffix);
			}
};

template<>
	inline std::string
	Convert::toString<std::string>(const std::string &t, int)
	{
		return (t);
	}

template<>
	inline std::string
	Convert::toString<Object>(const Object &t, int)
	{
		return (t.toString());
	}

#endif /* CONVERT_HPP_ */
