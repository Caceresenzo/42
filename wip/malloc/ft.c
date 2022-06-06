/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 20:15:10 by ecaceres          #+#    #+#             */
/*   Updated: 2022/06/06 20:15:10 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"

#include <stddef.h>
#include <string.h>
#include <sys/unistd.h>

void
ft_putchar(char c)
{
	write(1, &c, 1);
}

void
ft_putnbr(size_t n, size_t radix)
{
	if (n >= radix)
		ft_putnbr(n / radix, radix);
	ft_putchar("0123456789abcdef"[n % radix]);
}

void
ft_putnbr_dec(unsigned long n)
{
	ft_putnbr(n, 10);
}

void
ft_putnbr_hex(unsigned long n)
{
	ft_putnbr(n, 16);
}

void
ft_putstr(const char *str)
{
	write(1, str, strlen(str));
}
