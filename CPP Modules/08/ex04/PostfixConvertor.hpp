/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PostfixConvertor.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 11:59:26 by ecaceres          #+#    #+#             */
/*   Updated: 2020/07/20 11:59:26 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POSTFIXCONVERTOR_HPP_
# define POSTFIXCONVERTOR_HPP_

#include <stack>
#include <vector>

#include "OperatorToken.hpp"
#include "Token.hpp"

class PostfixConvertor
{
	private:
		int _top;
		std::vector<Token*> *_tokens;
		std::stack<Token*> _stack;

	public:
		PostfixConvertor();
		PostfixConvertor(std::vector<Token*> *tokens);
		PostfixConvertor(const PostfixConvertor &other);

		virtual ~PostfixConvertor();

		PostfixConvertor& operator=(const PostfixConvertor &other);

		bool isEmpty();

		Token* peek();

		Token* pop();
		void push(Token *token);

		bool isOperand(Token *token);

		bool notGreater(Token *token);

		bool convert(std::vector<Token*> &out);

		class PostfixException : public std::exception
		{
			private:
				std::string _message;

			public:
				PostfixException();
				PostfixException(std::string message);
				PostfixException(const PostfixException &other);

				virtual ~PostfixException() throw ();

			    virtual const char* what() const throw ();

			    PostfixException& operator=(const PostfixException &other);
		};
};

#endif /* POSTFIXCONVERTOR_HPP_ */
