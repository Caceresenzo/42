/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_size_test.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 14:55:00 by ecaceres          #+#    #+#             */
/*   Updated: 2019/12/02 14:55:00 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

static void
	do_test(char *name, size_t size)
{
	t_list	*list[2];
	size_t	result;

	ft_memset(&list, 0, sizeof(list));
	list_generate_sized((t_list **)list, size);
	result = ft_list_size(list[0]);
	list_display_header();
	list_display_result(name, (void *)result, (void *)size, LIST_AS_INT);
	printf("\n");
}

void
	test_ft_list_size(void)
{
	do_test("ft_list_size / size = 0", 0);
	do_test("ft_list_size / size = 10", 10);
	do_test("ft_list_size / size = 100", 100);
	do_test("ft_list_size / size = 1000", 1000);
	do_test("ft_list_size / size = 10000", 10000);
}
