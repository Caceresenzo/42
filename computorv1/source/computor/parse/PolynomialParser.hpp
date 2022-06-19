/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PolynomialParser.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 22:56:16 by ecaceres          #+#    #+#             */
/*   Updated: 2022/05/29 22:56:16 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POLYNOMIALPARSER_HPP_
# define POLYNOMIALPARSER_HPP_

#include <computor/Polynomial.hpp>
#include <core/io/StringReader.hpp>
#include <core/util/Optional.hpp>
#include <string>

class PolynomialParser
{
	public:
		typedef Polynomial<long double, int> polynomial_type;

	public:
		typedef enum
		{
			START,
			NUMBER,
			MULTIPLY,
			VARIABLE,
			CIRCUMFLEX,
			POWER,
			END,
		} State;

	private:
		StringReader m_reader;
		polynomial_type::map m_values;
		State m_state;
		Optional<bool> m_negate;
		Optional<polynomial_type::value_type> m_number_value;
		Optional<polynomial_type::exponent_type> m_exponent_value;

	public:
		PolynomialParser(const StringReader &reader);

	public:
		polynomial_type::map
		parse(void);

		bool
		consume();

		bool
		do_consume();

		void
		consume_number(bool is_floating, void *out);

		void
		commit(void);

		void
		commit_number(void);

		void
		commit_power(void);

		void
		reset(void);

		bool
		expected(const std::string &expectations);

		bool
		unexpected();

	public:
		static bool
		is_variable(char chr);

		static bool
		is_multiply(char chr);

		static bool
		is_circumflex(char chr);

		static bool
		is_dot(char chr);

		static bool
		is_sign(char chr);

		static bool
		is_minus(char chr);

		static bool
		is_plus(char chr);

		static bool
		is_end(char chr);

	public:
		static std::string
		to_string(State state);

		static polynomial_type
		parse(const std::string &input, std::string::size_type start, std::string::size_type end);
};

#endif /* POLYNOMIALPARSER_HPP_ */
