/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen_test.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 14:55:00 by ecaceres          #+#    #+#             */
/*   Updated: 2019/12/02 14:55:00 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

void
	test_ft_strlen(void)
{
	size_t		index;
	char		*str;
	size_t		length[2];

	list_display_header();
	index = 0;
	while ((str = g_strings[index]))
	{
		length[0] = strlen(str);
		length[1] = ft_strlen(str);
		list_display_result("ft_strlen", (void *)length[0],
										(void *)length[1], LIST_AS_INT);
		index++;
	}
	printf("\n");
}
