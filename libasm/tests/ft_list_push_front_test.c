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
	t_list *list[2];

	ft_memset(&list, 0, sizeof(list));
	ft_list_push_front(&(list[0]), "Hello");
	ft_list_push_front(&(list[0]), "World");
	ft_list_push_front(&(list[0]), "From");
	ft_list_push_front(&(list[0]), "42");
	ft_list_push_front_2(&(list[1]), "Hello");
	ft_list_push_front_2(&(list[1]), "World");
	ft_list_push_front_2(&(list[1]), "From");
	ft_list_push_front_2(&(list[1]), "42");
	list_display_content("ft_list_push_front", list, LIST_AS_STRING);
}
