/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 15:33:08 by ecaceres          #+#    #+#             */
/*   Updated: 2020/02/18 15:33:08 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_mshell	*g_shell = NULL;

void
	minishell_input_loop(t_mshell *shell)
{
	char	*line;
	int		ret;

	while (1)
	{
		minishell_prompt_ask(shell, 0);
		ret = get_next_line(IN, &line);
		if (line != NULL && ft_strlen(line) != 0)
			minishell_evaluate(shell, line);
		free(line);
		if (ret <= 0)
			break ;
	}
}
