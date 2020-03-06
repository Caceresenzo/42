/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_io_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 17:33:00 by ecaceres          #+#    #+#             */
/*   Updated: 2020/02/20 17:33:00 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int
	kind_to_open_mode(int kind)
{
	if (kind == TOKEN_KIND_INPUT)
		return (O_RDONLY);
	if (kind == TOKEN_KIND_OUTPUT)
		return (O_WRONLY | O_TRUNC | O_CREAT);
	if (kind == TOKEN_KIND_APPEND)
		return (O_WRONLY | O_APPEND | O_CREAT);
	return (-1);
}

t_token
	*token_create_io(int kind)
{
	int				open_mode;
	t_token			*tok;

	open_mode = kind_to_open_mode(kind);
	if (open_mode == -1)
		return (NULL);
	return (tok = token_create(kind, (void *)((long)0 + open_mode)));
}

int
	token_is_io(int kind)
{
	return (kind == TOKEN_KIND_INPUT
			|| kind == TOKEN_KIND_OUTPUT
			|| kind == TOKEN_KIND_APPEND);
}
