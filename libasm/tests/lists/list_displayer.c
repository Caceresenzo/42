/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_displayer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 19:16:17 by ecaceres          #+#    #+#             */
/*   Updated: 2019/08/05 19:16:20 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tests.h"

#define PRE "\e[33m%-30s\e[0m"

static char
	*list_get_result_word(int condition)
{
	return (condition ? "\e[92mOK\e[0m" : "\e[91mFAIL\e[0m");
}

void
	list_display_header(void)
{
	printf("%-30s | %4s | %40s %s\n", "NAME", "MATCH", "ASSEMBLY", "WORKING");
}

void
	list_display_content(char *name, t_list **list, int as)
{
	char	*result;

	list_display_header();
	while (list[0] && list[1])
	{
		list_display_result(name, list[0]->data, list[1]->data, as);
		list[0] = list[0]->next;
		list[1] = list[1]->next;
	}
	result = list_get_result_word(list[0] == NULL && list[1] == NULL);
	printf(PRE" | %-14s | %40p %p\n\n", name, result, list[0], list[1]);
}

void
	list_display_result(char *name, void *a, void *b, int as)
{
	char	*rslt;

	if (as == LIST_AS_STRING)
		rslt = list_get_result_word(strcmp((char *)a, (char *)b) == 0);
	else if (as == LIST_AS_INT)
		rslt = list_get_result_word(a == b);
	else if (as == LIST_AS_INT_FROM_PTR)
		rslt = list_get_result_word(*((int *)a) == *((int *)b));
	else
	{
		printf("unknown type.\n");
		return ;
	}
	if (as == LIST_AS_STRING)
		printf(PRE" | %-14s | %40s %s\n", name, rslt, (char *)a, (char *)b);
	else if (as == LIST_AS_INT)
		printf(PRE" | %-14s | %40d %d\n", name, rslt, (int)a, (int)b);
	else if (as == LIST_AS_INT_FROM_PTR)
		printf(PRE" | %-14s | %40d %d\n", name, rslt, *((int *)a), *((int *)b));
}
