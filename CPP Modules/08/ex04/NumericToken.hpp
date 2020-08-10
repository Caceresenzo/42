/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NumericToken.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 16:11:02 by ecaceres          #+#    #+#             */
/*   Updated: 2020/07/16 16:11:02 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NUMERICTOKEN_HPP_
# define NUMERICTOKEN_HPP_

#include "Token.hpp"

class NumericToken : public Token
{
	private:
		int _value;

	public:
		NumericToken();
		NumericToken(int value);
		NumericToken(const NumericToken &other);

		virtual ~NumericToken();

		NumericToken& operator=(const NumericToken &other);

		int value() const;

		virtual Token* clone() const;
		virtual std::string toString() const;
};

#endif /* NUMERICTOKEN_HPP_ */
