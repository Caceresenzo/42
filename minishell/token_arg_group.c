/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_arg_group.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 17:33:00 by ecaceres          #+#    #+#             */
/*   Updated: 2020/02/20 17:33:00 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token
	*token_create_string(char *string)
{
	t_token		*tok;
	char		*dup;

	if (!(dup = ft_strdup(string)))
		return (NULL);
	if (!(tok = token_create(TOKEN_KIND_STRING, dup)))
	{
		free(dup);
		return (NULL);
	}
	return (tok);
}
