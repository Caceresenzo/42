/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft.hpp                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atetu <atetu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 17:24:32 by ecaceres          #+#    #+#             */
/*   Updated: 2021/01/08 14:40:14 by atetu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_HPP_
# define FT_HPP_

#include <stddef.h>

namespace ft
{
	bool
	islower(char c);

	bool
	isupper(char c);

	void*
	memcpy(void *dest, const void *src, size_t len);

	void*
	memset(void *dest, char val, size_t len);

	void*
	bzero(void *dest, size_t len);

	size_t
	strlen(const char *str);

	char*
	strdup(const char *str);

	char*
	strchr(char *str, char c);

	char
	tolower(char c);

	char
	toupper(char c);

	bool
	isdigit(char c);

	int
	atoi(const char *str);
}

#endif /* FT_HPP_ */
