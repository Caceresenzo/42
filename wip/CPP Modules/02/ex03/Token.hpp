/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Token.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/04 16:56:11 by ecaceres          #+#    #+#             */
/*   Updated: 2020/01/04 16:56:11 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_HPP
# define TOKEN_HPP

# include "libft.hpp"

# include "Fixed.hpp"

typedef enum {
	kind_operator, kind_number, kind_list
} TokenKind;

class Token
{
	private:
		TokenKind kind;
		void *value;
		size_t position;
		bool converted;

	public:
		Token(char operatorChar, size_t positionInString);
		Token(Fixed *number, size_t positionInString);
		Token(t_list *lst, size_t positionInString);
		Token(Token **tokens, size_t positionInString);

		~Token(void);

		Token **convertListToArray(void);

		TokenKind getKind(void);
		void *getRawValue(void);
		size_t getPositionInString(void);

		char asOperatorChar(void);
		Fixed *asFixed(void);
		t_list *asList(void);
		Token **asArrayList(void);

		Token *duplicate(void);

		static size_t size(Token **array);
};

#endif /* TOKEN_HPP_ */
