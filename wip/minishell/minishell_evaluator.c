/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_evaluator.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 12:16:56 by ecaceres          #+#    #+#             */
/*   Updated: 2020/02/19 12:16:56 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int
	minishell_evaluate_next_tokens(t_arrlst **tokenlst, size_t *sub, char *line)
{
	if (!(*tokenlst = arraylist_create(10, NULL)))
		return (0);
	return (eval_tokens(*tokenlst, line, sub));
}

static int
	minishell_execute_process(t_mshell *shell, t_arrlst *processlst)
{
	t_process	*process;
	size_t		index;
	int			err;

	err = 0;
	index = 0;
	while (index != processlst->size)
	{
		process = (t_process *)processlst->items[index++];
		if (process == NULL)
			break ;
		arraylist_add(process->arglst, NULL);
		process->name = process->arglst->items[0];
		process->name = process->name == NULL ? NULL : ft_strdup(process->name);
		if (process->name == NULL)
		{
			minishell_error_simple(shell, ERR_UNEXPECTED);
			err = 1;
			break ;
		}
	}
	process_execute_list(processlst);
	arraylist_clear(processlst, &process_destroy);
	return (err);
}

static int
	handled_executor_builder(t_arrlst *toklst, t_arrlst *processlst)
{
	size_t		index;
	int			ret;
	t_token		*tok;

	index = 0;
	ret = executor_builder(&index, toklst, processlst);
	if (ret == EB_ERR_OPEN_FAIL)
	{
		tok = (t_token *)(toklst->items[index == 0 ? 0 : index - 1]);
		shell_error_file(g_shell, tok != NULL &&
			tok->kind == TOKEN_KIND_STRING ? tok->value : "", errno);
	}
	else if (ret != 0)
	{
		minishell_error_simple(g_shell, (char *[]){
				NULL,
				EB_ERR_NO_NEXT_T,
				EB_ERR_SYNTAX_T,
				EB_ERR_EMPTY_NEXT_T,
				NULL,
				EB_ERR_NO_NAME_T
		}[ret]);
	}
	return (ret);
}

void
	minishell_evaluate(t_mshell *shell, char *line)
{
	t_arrlst	*processlst;
	size_t		sub;
	t_arrlst	*tokenlst;
	int			ret[2];
	int			err;

	while (1)
	{
		sub = 0;
		ret[0] = minishell_evaluate_next_tokens(&tokenlst, &sub, line);
		processlst = arraylist_create(5, NULL);
		ret[1] = handled_executor_builder(tokenlst, processlst);
		err = minishell_execute_process(shell, processlst);
		arraylist_destroy(processlst);
		arraylist_clear(tokenlst, &token_destroy_sub);
		arraylist_destroy(tokenlst);
		line += sub;
		if (*line == '\0' || !ret[0] || ret[1] || err)
			break ;
	}
}
