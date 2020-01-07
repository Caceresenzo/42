/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Evaluator.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/04 16:56:11 by ecaceres          #+#    #+#             */
/*   Updated: 2020/01/04 16:56:11 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVALUATOR_HPP
# define EVALUATOR_HPP

# include "libft.hpp"

# include "Token.hpp"
# include "Fixed.hpp"

class Evaluator
{
	private:
		size_t problemPosition;
		std::string errorReason;

	public:
		Evaluator(void);

		Fixed evaluate(Token *tokens[], size_t position = 1);
		Fixed evaluate(Token *token);
		Fixed useOperator(Fixed &left, Fixed &right, char operatorChar, Token *token);

		void setError(size_t problemPosition, std::string errorReason);

		bool hasFoundError(void);
		size_t getProblemPosition(void);
		std::string getErrorReason(void);
};

#endif /* EVALUATOR_HPP_ */
