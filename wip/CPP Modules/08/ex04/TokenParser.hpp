/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TokenParser.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 13:32:30 by ecaceres          #+#    #+#             */
/*   Updated: 2020/07/20 13:32:30 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENPARSER_HPP_
# define TOKENPARSER_HPP_

#include <stddef.h>
#include <iostream>
#include <vector>

#include "Token.hpp"

class TokenParser
{
	private:
		const std::string _expr;

	public:
		TokenParser();
		TokenParser(std::string expr);
		TokenParser(const TokenParser &other);

		virtual ~TokenParser();

		TokenParser& operator=(const TokenParser &other);

		bool parse(std::vector<Token*> &out) const;

		static Token *tokenFromCharacter(char c, std::string expr, size_t &index);

		static std::string pretty(std::vector<Token*> &tokens);

		static bool errorAt(std::string expr, size_t position);
		static bool errorAt(std::string expr, std::string error);
		static bool errorAt(std::string expr, std::string error, size_t position);
};

#endif /* TOKENPARSER_HPP_ */
