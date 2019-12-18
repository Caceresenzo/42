/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_push_front_test.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 14:55:00 by ecaceres          #+#    #+#             */
/*   Updated: 2019/12/02 14:55:00 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

void
	test_ft_list_push_front(void)
{
	t_list *lst;

	lst = NULL;
	ft_list_push_front(&lst, "Hello");
	ft_list_push_front(&lst, "World");
	ft_list_push_front(&lst, "From");
	ft_list_push_front(&lst, "42");
	printf("%p\n", lst);
	fflush(stdout);
	printf("..%s..\n", (char *)(lst->data));
	printf("..%s..\n", (char *)(lst->next->data));
	printf("..%s..\n", (char *)(lst->next->next->data));
	printf("..%s..\n", (char *)(lst->next->next->next->data));
	printf("..%p..\n", (char *)(lst->next->next->next->next));
}
