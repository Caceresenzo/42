/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_remove_if_test.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 14:55:00 by ecaceres          #+#    #+#             */
/*   Updated: 2019/12/02 14:55:00 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

void
	xfree(void *ptr)
{
	if (MORE_DEBUG)
		printf("freed %d\n", *((int *)ptr));
	free(ptr);
}

int
	everything(void *data, void *data_ref)
{
	(void)data;
	(void)data_ref;
	return (0);
}

int
	compare_modulo(void *data, void *data_ref)
{
	if (data == NULL && MORE_DEBUG)
		printf("WARNING: data %p ref %p\n", data, data_ref);
	return (*((int *)data) % ((int)data_ref));
}

static void
	do_test(char *name, int (*cmp)(), void *data_ref)
{
	t_list	*list[2];

	ft_memset(&list, 0, sizeof(list));
	list_generate((t_list **)list);
	ft_list_remove_if(&(list[0]), data_ref, cmp, &xfree);
	ft_list_remove_if_2(&(list[1]), data_ref, cmp, &xfree);
	list_display_content(name, list, LIST_AS_INT_FROM_PTR);
}

void
	test_ft_list_remove_if(void)
{
	do_test("ft_list_remove_if / EVERYTHING", &everything, 0);
	do_test("ft_list_remove_if / MODULE 1", &compare_modulo, (void *)1);
	do_test("ft_list_remove_if / MODULE 2", &compare_modulo, (void *)2);
	do_test("ft_list_remove_if / MODULE 3", &compare_modulo, (void *)3);
	do_test("ft_list_remove_if / MODULE 4", &compare_modulo, (void *)4);
	do_test("ft_list_remove_if / MODULE 5", &compare_modulo, (void *)5);
	do_test("ft_list_remove_if / MODULE 8", &compare_modulo, (void *)8);
}
