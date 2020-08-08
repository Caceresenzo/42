/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   microshell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 12:01:53 by ecaceres          #+#    #+#             */
/*   Updated: 2020/08/08 12:01:53 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MICROSHELL_H
# define MICROSHELL_H

# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <errno.h>

# define FD_IN 0
# define FD_OUT 1
# define FD_ERR 2

typedef enum
{
	TT_STRING = 0,
	TT_PIPE,
	TT_SEMICOLON
} t_ttype;

typedef struct
{
	t_ttype type;
	char *data;
	bool end;
} t_token;

typedef struct
{
	char *path;
	char **args;
	bool piped;
	bool semicoloned;
	pid_t pid;
} t_program;

void*
malloc_zeros(size_t size);

size_t
ft_strlen(char *str);

void
ft_putstr(int fd, char *str);

#endif
