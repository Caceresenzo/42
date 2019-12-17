/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libasm.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 11:12:23 by ecaceres          #+#    #+#             */
/*   Updated: 2019/08/01 11:12:23 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBASM_H
# define LIBASM_H

# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>

/*
** http://www.lacl.fr/tan/asm
*/

extern void		*malloc(size_t size);
extern char		*strcpy(char *__dst, const char *__src);
extern size_t	strlen(const char *__s);

extern size_t	ft_strlen(const char *s);
extern char		*ft_strcpy(char *dst, const char *src);
extern int		ft_strcmp(const char *s1, const char *s2);
extern char		*ft_strdup(const char *s1);

extern ssize_t	ft_write(int fildes, const void *buf, size_t nbyte);
extern ssize_t	ft_read(int fildes, void *buf, size_t nbyte);

extern int		ft_atoi_base(const char *str, const char *base);
extern int		ft_atoi_base_resolve(const char *str, const char c);

#endif
