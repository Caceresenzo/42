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

#include <exception/IllegalArgumentException.hpp>
#include <libs/ft.hpp>
#include <util/Convert.hpp>
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
			parse(const std::string &text, const std::string &alphabet = DECIMAL)
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
					char c = *it;
					char u = ft::toupper(c);

					std::string::size_type pos = alphabet.find(u);
					if (pos == std::string::npos)
						throw IllegalArgumentException(std::string("char `") + c + "` is not in the alphabet: `" + alphabet + '`');

					out *= alphabet.size();
					out += pos;
				}

				out *= negativity;

				T min = std::numeric_limits<T>::min();
				T max = std::numeric_limits<T>::max();

				if (out < min)
					throw IllegalArgumentException(Convert::toString(out) + " < " + Convert::toString(min) + " (type's minimum)");

				if (out > max)
					throw IllegalArgumentException(Convert::toString(out) + " > " + Convert::toString(max) + " (type's maximum)");

				return (T(out));
			}
};

#endif /* NUMBER_HPP_ */
