/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putuchar_fd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 13:45:19 by ecaceres          #+#    #+#             */
/*   Updated: 2019/11/05 13:45:19 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#define UTF8_CP1 0x80
#define UTF8_CP2 0x800
#define UTF8_CP3 0x10000
#define UTF8_CP4 0x200000

#define UTF8_BX 0x80
#define UTF8_B2 0xC0
#define UTF8_B3 0xE0
#define UTF8_B4 0xF0
#define UTF8_B5 0xF8

/*
** Help:
** http://defeo.lu/in420/Coder%20et%20d%C3%A9coder%20en%20UTF-8%20et%20UTF-16
*/

void
	ft_putuchar_fd(int c, int fd)
{
	unsigned char	chr;

	if ((unsigned char)c >= UTF8_CP1)
	{
		chr = (unsigned char)c / 0x40 + UTF8_B2;
		write(fd, &chr, 1);
		chr = (unsigned char)c % 0x40 + UTF8_BX;
		write(fd, &chr, 1);
	}
	else
		write(fd, &c, 1);
}
