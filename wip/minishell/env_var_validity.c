/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_validity.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 19:22:10 by ecaceres          #+#    #+#             */
/*   Updated: 2020/02/20 19:22:10 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** [a-zA-Z_]+[a-zA-Z0-9_]*
*/

int
	env_var_is_name_valid(char *name, int allow_eq)
{
	if (name == NULL)
		return (0);
	if (!ft_isalpha(*name) && *name != '_')
		return (0);
	name++;
	while (*name)
	{
		if (allow_eq && (*name == '=' || (*name == '+' && *(name + 1) == '=')))
			break ;
		if (!ft_isalnum(*name) && !ft_isdigit(*name) && *name != '_')
			return (0);
		name++;
	}
	return (1);
}

int
	env_var_is_name_valid_len(char *name)
{
	char	*start;

	start = name;
	if (name != NULL && (ft_isalpha(*name) || *name == '_'))
	{
		name++;
		while (*name)
		{
			if (!ft_isalnum(*name) && !ft_isdigit(*name) && *name != '_')
				break ;
			name++;
		}
	}
	return (name - start);
}
