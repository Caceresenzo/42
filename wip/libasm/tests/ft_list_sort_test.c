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
	do_test(char *name, int (*cmp)(), int index)
{
	int		*malloced_index;
	t_list	*list[2];

	list[0] = ft_create_elem(0);
	list[1] = ft_create_elem(0);
	while (++index < 27)
	{
		malloced_index = malloc(sizeof(int));
		*malloced_index = index;
		ft_list_push_back(&(list[0]), (void *)malloced_index);
		ft_list_push_back(&(list[1]), (void *)malloced_index);
	}
	ft_list_sort(&(list[0]->next), cmp);
	ft_list_sort_2(&(list[1]->next), cmp);
	printf("%20s %s %20s\n", "WORKING", "ASSEMBLY", name);
	list[0] = list[0]->next;
	list[1] = list[1]->next;
	index = 0;
	while (++index < 27)
	{
		printf("%20d %d\n", *((int *)list[0]->data), *((int *)list[1]->data));
		list[0] = list[0]->next;
		list[1] = list[1]->next;
	}
}

void
	test_ft_list_sort(void)
{
	do_test("LESS THAN", &less_than, 0);
	do_test("MORE THAN", &more_than, 0);
	do_test("EVEN FIRST", &even_first, 0);
}
