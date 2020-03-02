/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evaluator_env_var.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 18:42:26 by ecaceres          #+#    #+#             */
/*   Updated: 2020/02/20 18:42:26 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int
	consume_last_code(char *line, size_t *consumed, t_arrlst *chrlst)
{
	char	*itoa;

	eval_consume(1, &line, consumed, 0);
	itoa = ft_itoa(0 + g_shell->last_code);
	if (itoa != NULL)
		arg_builder_add_string(chrlst, itoa, 0);
	free(itoa);
	return (1);
}

static int
	consume_env_var(char *line, size_t *consumed, t_arrlst *chrlst, size_t len)
{
	size_t		index;
	t_env_var	*var;
	t_env_var	*found;

	index = 0;
	found = NULL;
	while (index < g_env_variables.size)
	{
		var = (t_env_var *)g_env_variables.items[index];
		index++;
		if (var->name_len != len)
			continue ;
		if (ft_strncmp(line, var->name, len) == 0)
			if (found == NULL || found->name_len < var->name_len)
				found = var;
	}
	if (found && found->value != NULL)
		arg_builder_add_string(chrlst, found->value, 0);
	return (eval_consume(found ? found->name_len : len, &line, consumed, 1));
}

int
	eval_env_var(char *line, size_t *consumed, t_arrlst *chrlst)
{
	size_t		len;

	if (*line != '$')
		return (0);
	eval_consume(1, &line, consumed, 0);
	len = 0 + env_var_is_name_valid_len(line);
	if (len == 0)
	{
		if (*line == '?')
			return (consume_last_code(line, consumed, chrlst));
		arg_builder_add_char(chrlst, '$', 0);
		return (1);
	}
	return (consume_env_var(line, consumed, chrlst, len));
}
