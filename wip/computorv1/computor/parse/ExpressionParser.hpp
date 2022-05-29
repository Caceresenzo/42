/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ExpressionParser.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 22:04:49 by ecaceres          #+#    #+#             */
/*   Updated: 2022/05/29 22:04:49 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPRESSIONPARSER_HPP_
# define EXPRESSIONPARSER_HPP_

#include <computor/Polynomial.hpp>

class ExpressionParser
{
	public:
		typedef Polynomial<long double, int> polynomial_type;

	public:
		static std::pair<polynomial_type, polynomial_type>
		parse(const std::string &input);

		static polynomial_type
		parse(const std::string &input, std::string::size_type start, std::string::size_type end);
};

#endif /* EXPRESSIONPARSER_HPP_ */
