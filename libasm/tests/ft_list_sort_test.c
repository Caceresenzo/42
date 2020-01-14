/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_sort_test.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 14:55:00 by ecaceres          #+#    #+#             */
/*   Updated: 2019/12/02 14:55:00 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

int
	more_than(void *a, void *b)
{
	return ((*(int *)a) > (*(int *)b));
}

int
	less_than(void *a, void *b)
{
	return ((*(int *)a) < (*(int *)b));
}

int
	even_first(void *a, void *b)
{
	int		c;
	int		d;
	int		r;

	c = (*(int *)a);
	d = (*(int *)b);
	if ((c % 2 != 0) && (d % 2 == 0))
		r = (1);
	else if ((c % 2 == 0) && (d % 2 != 0))
		r = (-1);
	else
		r = (0);
	return (r);
}

static void
	do_test(char *name, int (*cmp)())
{
	t_list	*list[2];

	ft_memset(&list, 0, sizeof(list));
	list_generate((t_list **)list);
	ft_list_sort(&(list[0]->next), cmp);
	ft_list_sort_2(&(list[1]->next), cmp);
	list[0] = list[0]->next;
	list[1] = list[1]->next;
	list_display_content(name, list, LIST_AS_INT_FROM_PTR);
}

void
	test_ft_list_sort(void)
{
	do_test("ft_list_sort / LESS THAN", &less_than);
	do_test("ft_list_sort / MORE THAN", &more_than);
	do_test("ft_list_sort / EVEN FIRST", &even_first);
}
