/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argument_builder.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 15:22:18 by ecaceres          #+#    #+#             */
/*   Updated: 2020/02/19 15:22:18 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	arg_builder_initialize(t_arrlst *chrlst)
{
	arraylist_init(chrlst, NULL, 100);
	arraylist_grow(chrlst, 100);
}

void
	arg_builder_finalize(t_arrlst *chrlst)
{
	arraylist_destroy_items(chrlst);
}

void
	arg_builder_add_string(t_arrlst *chrlst, char *str, char quote)
{
	size_t	len;
	size_t	index;

	len = ft_strlen(str);
	arraylist_grow(chrlst, len);
	index = 0;
	while (index < len)
	{
		arraylist_add_char(chrlst, str[index]);
		arg_builder_debug_print_char(str[index], quote);
		index++;
	}
}

void
	arg_builder_add_char(t_arrlst *chrlst, char chr, char quote)
{
	arraylist_add_char(chrlst, chr);
	arg_builder_debug_print_char(chr, quote);
}

char
	*arg_builder_build(t_arrlst *chrlst)
{
	char	*arg;
	size_t	index;

	if (!(arg = (char *)malloc((chrlst->size + 1) * sizeof(char))))
		return (NULL);
	index = 0;
	while (index < chrlst->size)
	{
		arg[index] = (char)(0 + chrlst->items[index]);
		index++;
	}
	arg[index] = '\0';
	return (arg);
}
