/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Token.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/04 16:56:11 by ecaceres          #+#    #+#             */
/*   Updated: 2020/01/04 16:56:11 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Token.hpp"

static void
free_token_by_delete(void *content)
{
	Token *token = (Token *)content;

	delete token;
}

static void
free_nothing(void *content)
{
	(void)content;
}

Token::Token(void)
{
	this->kind = kind_operator;
	this->value = (void *)(long)'+';
	this->position = 0;

	this->converted = false;
}

Token::Token(char operatorChar, size_t positionInString)
{
	this->kind = kind_operator;
	this->value = (void *)(long)operatorChar;
	this->position = positionInString;

	this->converted = false;
}

Token::Token(Fixed *fixed, size_t positionInString)
{
	this->kind = kind_number;
	this->value = fixed;
	this->position = positionInString;

	this->converted = false;
}

Token::Token(t_list *lst, size_t positionInString)
{
	this->kind = kind_list;
	this->value = (void *)lst;
	this->position = positionInString;

	this->converted = false;
}

Token::Token(Token **tokens, size_t positionInString)
{
	this->kind = kind_list;
	this->value = (void *)tokens;
	this->position = positionInString;

	this->converted = true;
}

Token::~Token(void)
{
	switch (this->kind)
	{
		case kind_operator:
		{
			break ;
		}

		case kind_number:
		{
			delete asFixed();
			break ;
		}

		case kind_list:
		{
			if (converted)
			{
				Token **tokens = asArrayList();

				Token *token;
				for (size_t index = 0; (token = tokens[index]); index++)
				{
					delete token;
				}

				free(tokens);
			}
			else
			{
				t_list *lst = asList();

				ft_lstclear(&lst, &free_token_by_delete);
			}
			break ;
		}
	}
}

Token &
Token::operator =(const Token &other)
{
	if (this != &other)
	{
		this->kind = other.kind;
		this->value = other.value;
		this->position = other.position;

		this->converted = other.converted;
	}

	return (*this);
}

Token **
Token::convertListToArray(void)
{
	if (this->kind != kind_list || this->converted)
	{
		return (NULL);
	}

	t_list *next = asList();

	if (next == NULL)
	{
		return (NULL);
	}

	int size = ft_lstsize(next);
	int byteSize = (size * sizeof(Token *)) + 1;
	Token **array = (Token **)malloc(byteSize);

	if (array != NULL)
	{
		array[size] = NULL;

		size_t index = 0;

		while (1)
		{
			Token *token = (Token *)next->content;

			if (token != NULL)
			{
				array[index] = token;

				if (token->getKind() == kind_list)
				{
					token->convertListToArray();
				}

				index++;
			}

			next = next->next;
			if (next == NULL)
			{
				break ;
			}
		}
	}

	t_list *lst = asList();
	ft_lstclear(&lst, &free_nothing);

	this->value = (void *)array;
	this->converted = true;

	return (array);
}

TokenKind
Token::getKind(void)
{
	return (this->kind);
}

void *
Token::getRawValue(void)
{
	return (this->value);
}

size_t
Token::getPositionInString(void)
{
	return (this->position);
}

char
Token::asOperatorChar(void)
{
	if (this->kind == kind_operator)
	{
		return ((char)((long)this->value & 0xFF));
	}

	return (0);
}

Fixed *
Token::asFixed(void)
{
	if (this->kind == kind_number)
	{
		return ((Fixed *)this->value);
	}

	return (NULL);
}

t_list *
Token::asList(void)
{
	if (this->kind == kind_list)
	{
		return ((t_list *)this->value);
	}

	return (NULL);
}

Token **
Token::asArrayList(void)
{
	if (this->kind == kind_list)
	{
		return ((Token **)this->value);
	}

	return (NULL);
}

size_t
Token::size(Token **array)
{
	size_t size = 0;

	if (array != NULL)
	{
		while (array[size])
		{
			size++;
		}
	}

	return (size);
}
