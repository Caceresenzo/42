/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 20:14:38 by ecaceres          #+#    #+#             */
/*   Updated: 2022/06/06 20:14:38 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_H
# define FT_H

#include <stddef.h>

#define COLOR_RED "\e[31m"
#define COLOR_GREEN "\e[32m"
#define COLOR_YELLOW "\e[33m"
#define COLOR_BLUE "\e[34m"
#define COLOR_RESET "\e[0m"

void
ft_putchar(char c);

void
ft_putnbr(size_t n, size_t radix);

void
ft_putnbr_dec(unsigned long n);

void
ft_putnbr_hex(unsigned long n);

void
ft_putstr(const char *str);

#endif
