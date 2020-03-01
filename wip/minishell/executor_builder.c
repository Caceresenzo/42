/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_builder.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 12:19:17 by ecaceres          #+#    #+#             */
/*   Updated: 2020/02/21 12:19:17 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_process
	*new(void)
{
	t_process	*process;

	if (!(process = malloc(sizeof(t_process))))
		return (NULL);
	ft_memset(process, 0, sizeof(t_process));
	process->in_fd = -1;
	process->out_fd = -1;
	process->arglst = arraylist_create(10, NULL);
	return (process);
}

static t_token
	*n_tok(t_arrlst *toklst, size_t *index, int increment)
{
	t_token		*tok;

	tok = toklst->items[*index];
	*index += increment;
	return (tok);
}

static int
	builder_io(t_process *process, t_arrlst *toklst, size_t *index)
{
	t_token			*tok;
	t_token			*next;
	int				*fd;

	tok = toklst->items[*index - 2];
	next = toklst->items[*index - 1];
	fd = tok->kind == TOKEN_KIND_INPUT ? &(process->in_fd) : &(process->out_fd);
	if (*fd != -1)
		close(*fd);
	*fd = open((char *)(next->value), (int)(0 + tok->value), 0644);
	return (*fd == -1);
}

static int
	single(t_process **process_ptr, t_arrlst *processlst,
			t_arrlst *lst, size_t *i)
{
	t_token			*tok;
	t_token			*nxt;

	if ((tok = lst->items[*i - 1])->kind == TOKEN_KIND_SEMICOLON)
		return (-1);
	if (tok->kind == TOKEN_KIND_PIPE)
	{
		if ((nxt = n_tok(lst, i, 0)) == NULL || nxt->kind != TOKEN_KIND_STRING)
			return (EB_ERR_SYNTAX);
		arraylist_add(processlst, *process_ptr);
		*process_ptr = new();
		return (-2);
	}
	else if (tok->kind == TOKEN_KIND_STRING)
		arraylist_add((*process_ptr)->arglst, ft_strdup((char *)tok->value));
	else if (token_is_io(tok->kind))
	{
		if ((nxt = n_tok(lst, i, 1)) == NULL || nxt->kind != TOKEN_KIND_STRING)
			return (EB_ERR_NO_NEXT);
		if (builder_io(*process_ptr, lst, i))
			return (EB_ERR_OPEN_FAIL);
	}
	return (0);
}

int
	executor_builder(size_t *index, t_arrlst *toklst, t_arrlst *processlst)
{
	t_token		*tok;
	t_process	*process;
	int			r;

	process = new();
	arraylist_grow(toklst, 1);
	*index = 0;
	while (*index < toklst->size)
	{
		tok = toklst->items[*index];
		*index += 1;
		if (tok == NULL)
			break ;
		r = single(&process, processlst, toklst, index);
		if (r == -2)
			continue ;
		if ((process->arglst->size == 0 ? r = EB_ERR_NO_NAME : 0) || r == -1)
			break ;
		if (r > 0)
			return (process_destroy2(process, r));
	}
	if (process != NULL)
		arraylist_add(processlst, process);
	return (0);
}
