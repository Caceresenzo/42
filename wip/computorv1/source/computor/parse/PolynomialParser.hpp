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
			NEGATE,
			NUMBER,
			MULTIPLY,
			VARIABLE,
			CIRCUMFLEX,
			POWER,
			END,
		} State;

	private:
		polynomial_type::map m_values;
		State m_state;
		bool m_negate;
		std::string m_number;

		Optional<polynomial_type::value_type> m_number_value;
		Optional<polynomial_type::exponent_type> m_exponent_value;

	public:
		PolynomialParser(void);

	public:
		bool
		consume(char character, std::string::size_type index);

		bool
		do_consume(char character, std::string::size_type index);

		void
		commit(std::string::size_type next_index);

		void
		commit_number(std::string::size_type next_index);

		void
		commit_power(std::string::size_type next_index);

		void
		reset(void);

		bool
		expected(const std::string &expectations, std::string::size_type index);

		bool
		unexpected(std::string::size_type index);

		void
		ensure_number_not_empty(std::string::size_type index);

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
