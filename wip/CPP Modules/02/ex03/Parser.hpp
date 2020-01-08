/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/04 16:56:11 by ecaceres          #+#    #+#             */
/*   Updated: 2020/01/04 16:56:11 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_HPP
# define PARSER_HPP

# include <string>

# include "libft.hpp"

# include "Token.hpp"

class Parser
{
	private:
		Token **tokens;

		Token *problematicToken;
		std::string errorReason;

	public:
		Parser(void);
		Parser(Token **tokens);
		Parser(const Parser &other);

		~Parser(void);

		Parser &operator =(const Parser &other);

		bool parse(void);

		void validate(Token **tokens);

		void setError(Token *problematicToken, std::string errorReason);

		bool hasFoundError(void);
		Token *getProblematicToken(void);
		std::string getErrorReason(void);
};

#endif /* PARSER_HPP_ */
