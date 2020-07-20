/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Token.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 16:08:32 by ecaceres          #+#    #+#             */
/*   Updated: 2020/07/16 16:08:32 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_HPP_
# define TOKEN_HPP_

# include <string>
# include <iostream>
# include <vector>

class Token
{
	public:
		Token();
		Token(const Token &other);

		virtual ~Token();

		Token& operator=(const Token &other);

		virtual Token* clone() const = 0;
		virtual std::string toString() const = 0;

		static std::string join(std::vector<Token*> const &tokens);
		static void free(std::vector<Token*> &tokens);
};

std::ostream& operator<<(std::ostream& stream, const Token *token);

#endif /* TOKEN_HPP_ */
