/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Number.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 15:24:43 by ecaceres          #+#    #+#             */
/*   Updated: 2020/07/01 15:24:43 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NUMBER_HPP_
# define NUMBER_HPP_

# include <string>
# include <climits>
# include <exception>

# define SCHAR_MIN_AS_DOUBLE (static_cast<double>(SCHAR_MIN))
# define SCHAR_MAX_AS_DOUBLE (static_cast<double>(SCHAR_MAX))
# define INT_MIN_AS_DOUBLE (static_cast<double>(INT_MIN))
# define INT_MAX_AS_DOUBLE (static_cast<double>(INT_MAX))

# if !defined(COLORED) or !COLORED

# define COLOR_RESET ""
# define COLOR_TYPES ""
# define COLOR_NUMBER ""
# define COLOR_FAILED ""

# else

# define COLOR_RESET "\e[0m"
# define COLOR_TYPES "\e[92m"
# define COLOR_NUMBER "\e[93m"
# define COLOR_FAILED "\e[91m"

# endif

class Number
{
	private:
		int _precision;
		double _value;

		double ensureParsing(bool nanIsFailure);

	public:
		Number();
		Number(const std::string raw);
		Number(const Number &other);

		virtual ~Number();

		Number& operator=(const Number &other);

		char asChar();
		int asInt();
		float asFloat();
		double asDouble();

		int precision();

		static double parseDouble(std::string str, int *precision);
		static bool dump(std::string str);
		static void dump(Number number);

		class NumberException : public std::exception
		{
			private:
				const std::string _message;
				const size_t _position;

			public:
				NumberException(void);
				NumberException(std::string message);
				NumberException(std::string message, size_t position);
				NumberException(const NumberException &other);

				virtual ~NumberException(void) throw ();

				NumberException& operator=(const NumberException &other);

				virtual const char* what() const throw ();

				const std::string &message() const;
				const size_t &position() const;

				static NumberException invalidFormat(std::string reason);
				static NumberException invalidFormat(std::string reason, size_t position);
				static NumberException impossible();
				static NumberException nonDisplayable();
		};
};

#endif /* NUMBER_HPP_ */
