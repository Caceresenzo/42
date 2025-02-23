/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 18:16:33 by ecaceres          #+#    #+#             */
/*   Updated: 2022/05/21 18:16:33 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_H
# define FT_H

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

# define MIN(a, b) (((a) < (b)) ? (a) : (b))
# define MAX(a, b) (((a) > (b)) ? (a) : (b))

int
ft_islower(int c);

int
ft_toupper(int c);

size_t
ft_strlen(const char *str);

size_t
ft_strnlen(const char *str, size_t max);

int
ft_strncmp(const char *s1, const char *s2, size_t n);

int
ft_strcmp(const char *s1, const char *s2);

bool
ft_strstartswith(const char *str, const char *prefix);

void*
ft_calloc(size_t count, size_t size);

void*
ft_memset(void *src, int c, size_t n);

ssize_t
ft_putchar_fd(char c, int fd);

ssize_t
ft_putstr_fd(const char *s, int fd);

void
ft_bzero(void *s, size_t n);

int
ft_memcmp(const void *s1, const void *s2, size_t n);

char*
ft_itoa(long n, char *string, int radix);

char*
ft_strchr(const char *s, int c);

void*
ft_memchr(const void *s, int c, size_t n);

#endif
