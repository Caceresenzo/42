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
#include <stdbool.h>
#include <stdarg.h>
#include <unistd.h>
#include <string.h>

#define COLOR_RED "\e[31m"
#define COLOR_GREEN "\e[32m"
#define COLOR_YELLOW "\e[33m"
#define COLOR_BLUE "\e[34m"
#define COLOR_RESET "\e[0m"

int
ft_tolower(int c);

int
ft_isupper(int c);

ssize_t
ft_putchar_fd(char c, int fd);

ssize_t
ft_putunbr_fd(unsigned long n, size_t radix, int fd);

ssize_t
ft_putunbr_fd_dec(unsigned long n, int fd);

ssize_t
ft_putunbr_fd_hex(unsigned long n, int fd);

ssize_t
ft_putstr_fd(const char *str, int fd);

size_t
ft_strlen(const char *str);

int
ft_strcasecmp(const char *left, const char *right);

int
ft_printf(const char *format, ...);

int
ft_dprintf(int fd, const char *format, ...);

int
ft_vprintf(const char *format, va_list args);

int
ft_vdprintf(int fd, const char *format, va_list args);

#endif
