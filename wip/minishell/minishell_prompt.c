/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_prompt.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 16:36:36 by ecaceres          #+#    #+#             */
/*   Updated: 2020/02/20 16:36:36 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	minishell_prompt_ask(t_mshell *shell, int with_new_line)
{
	if (with_new_line)
		ft_putchar_fd('\n', OUT);
	ft_putstr_fd(shell->name, OUT);
	ft_putstr_fd("$ ", OUT);
}
