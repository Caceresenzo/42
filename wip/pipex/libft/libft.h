/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 23:10:03 by ecaceres          #+#    #+#             */
/*   Updated: 2021/06/10 23:10:03 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stdbool.h>

# define STDIN 0
# define STDOUT 1
# define STDERR 2

size_t	ft_strlen(const char *str);
char	*ft_strdup(const char *str);
char	*ft_strchr(const char *str, char c);
ssize_t	ft_write(int fd, const char *str);
int		ft_strncmp(const char *str1, const char *str2, size_t n);

void	*ft_memset(void *dest, char c, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);

void	*ft_bzero(void *str, size_t n);

void	*ft_zalloc(size_t size);
void	*ft_calloc(size_t n, size_t size);

#endif
