/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lexer.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/04 16:56:11 by ecaceres          #+#    #+#             */
/*   Updated: 2020/01/04 16:56:11 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_HPP
# define LEXER_HPP

# include <string>
# include <stddef.h>

# include "libft.hpp"

# define LEXER_EOF 0
# define LEXER_ERR 1

class Lexer
{
	private:
		std::string expression;
		size_t index;
		int depth;
		bool error;

		char eat(void);
		void process(t_list *&lst);
		float readFloat(void);

	public:
		Lexer(std::string expression);

		bool analyze(t_list *&lst);

		std::string getExpression();
		size_t getCurrentIndex(void);
		int getCurrentDepth(void);
		bool hasFoundError(void);
};

#endif /* LEXER_HPP_ */
