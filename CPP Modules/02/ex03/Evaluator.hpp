/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Evaluator.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 15:55:46 by ecaceres          #+#    #+#             */
/*   Updated: 2020/06/18 15:55:46 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVALUATOR_HPP_
# define EVALUATOR_HPP_

# include "ArrayList.hpp"
# include "Token.hpp"
# include "Fixed.hpp"
# include "TokenReader.hpp"
# include "NumberToken.hpp"

class Evaluator : public TokenReader
{
	private:
		NumberToken *useOperator(const Token *right, const Token *left, const Token *operatorToken);

		static bool hasPrecedence(const Token *operator1, const Token *operator2);

	public:
		Evaluator(void);
		Evaluator(ArrayList &list);
		Evaluator(const Evaluator &other);

		virtual ~Evaluator(void);

		Evaluator& operator =(const Evaluator &other);

		Fixed evaluate(void);
};

#endif /* EVALUATOR_HPP_ */
