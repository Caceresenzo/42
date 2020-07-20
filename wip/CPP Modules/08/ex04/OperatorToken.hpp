/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OperatorToken.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 16:11:02 by ecaceres          #+#    #+#             */
/*   Updated: 2020/07/16 16:11:02 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPERATORTOKEN_HPP_
# define OPERATORTOKEN_HPP_

# include <exception>
# include <iostream>

# include "Token.hpp"

enum OperatorType
{
	OP_ADD,
	OP_SUBSTRACT,
	OP_MULTIPLY,
	OP_DEVIDE,
	OP__LENGTH,
};

class OperatorToken : public Token
{
	private:
		OperatorType _type;

	public:
		OperatorToken();
		OperatorToken(OperatorType type);
		OperatorToken(const OperatorToken &other);

		virtual ~OperatorToken();

		OperatorToken& operator=(const OperatorToken &other);

		int use(int left, int right);

		OperatorType type() const;
		char toChar() const;
		std::string english() const;

		virtual Token* clone() const;
		virtual std::string toString() const;

		class ArithmeticException : public std::exception
		{
			private:
				std::string _message;

			public:
				ArithmeticException();
				ArithmeticException(std::string message);
				ArithmeticException(const ArithmeticException &other);

				virtual ~ArithmeticException() throw ();

				ArithmeticException& operator=(const ArithmeticException &other);

			    virtual const char* what() const throw ();
		};
};

#endif /* OPERATORTOKEN_HPP_ */
