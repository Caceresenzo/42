/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ExpressionParser.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 22:19:24 by ecaceres          #+#    #+#             */
/*   Updated: 2022/05/29 22:19:24 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <computor/parse/ExpressionParser.hpp>
#include <computor/parse/ParseException.hpp>
#include <computor/parse/PolynomialParser.hpp>
#include <string>
#include <utility>

std::pair<ExpressionParser::polynomial_type, ExpressionParser::polynomial_type>
ExpressionParser::parse(const std::string &input)
{
	std::string::size_type equal_index = input.find('=');
	if (equal_index == std::string::npos)
		throw ParseException("no equal found");

	std::string::size_type next_equal_index = input.find('=', equal_index + 1);
	if (next_equal_index != std::string::npos)
		throw ParseException("multiple equal found", next_equal_index);

	polynomial_type left = parse(input, 0, equal_index);
#if defined(DEBUG) && DEBUG
	std::cout << "left=" << left << std::endl;
#endif

	polynomial_type right = parse(input, equal_index + 1, input.size());
#if defined(DEBUG) && DEBUG
	std::cout << "right=" << right << std::endl;
#endif

	return (std::make_pair(left, right));
}

ExpressionParser::polynomial_type
ExpressionParser::parse(const std::string &input, std::string::size_type start, std::string::size_type end)
{
#if defined(DEBUG) && DEBUG
	std::cout << "input=`" << input << "` " << "start=" << start << " " << "end=" << end << " " << "view=`" << input.substr(start, end) << "`" << std::endl;
#endif

	if (start == end)
		throw ParseException("nothing to work with", start);

	return (PolynomialParser::parse(input, start, end));
}
