/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Number.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 22:43:53 by ecaceres          #+#    #+#             */
/*   Updated: 2020/12/30 22:43:53 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NUMBER_HPP_
# define NUMBER_HPP_

#include <lang/Character.hpp>
#include <lang/IllegalArgumentException.hpp>
#include <lang/String.hpp>
#include <iterator>
#include <limits>
#include <string>

class Number
{
	public:
		static const std::string BIN;
		static const std::string DECIMAL;
		static const std::string HEX;

	private:
		Number();
		Number(const Number &other);

		virtual
		~Number();

		Number&
		operator=(const Number &other);

	public:
		template<typename T>
			static T
			parse_floating(const std::string &text)
			{
				std::stringstream stream;
				stream << text;

				T value = T();
				if (!(stream >> value))
					throw IllegalArgumentException("invalid number");

				return (value);
			}

		template<typename T>
			static T
			parse_integer(const std::string &text, const std::string &alphabet = DECIMAL)
			{
				if (alphabet.length() <= 1)
					throw IllegalArgumentException("alphabet's length <= 1");

				std::string::const_iterator it = text.begin();

				int negativity = 1;
				if (*it == '-')
				{
					negativity = -1;
					it++;
				}

				long long out = 0;
				for (; it != text.end(); it++)
				{
					char character = *it;
					char upper = Character::to_upper_case(character);

					std::string::size_type pos = alphabet.find(upper);
					if (pos == std::string::npos)
						throw IllegalArgumentException(std::string("char `") + character + "` is not in the alphabet: `" + alphabet + '`');

					out *= alphabet.size();
					out += pos;
				}

				out *= negativity;

				T min = std::numeric_limits<T>::min();
				T max = std::numeric_limits<T>::max();

				if (out < min)
					throw IllegalArgumentException(String::value_of<long long>(out) + " < " + String::value_of<long long>(min) + " (type's minimum)");

				if (out > max)
					throw IllegalArgumentException(String::value_of<long long>(out) + " > " + String::value_of<long long>(max) + " (type's maximum)");

				return (T(out));
			}
};

#endif /* NUMBER_HPP_ */
