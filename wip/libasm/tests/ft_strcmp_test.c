/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp_test.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 14:55:00 by ecaceres          #+#    #+#             */
/*   Updated: 2019/12/02 14:55:00 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

void
	test_ft_strcmp(void)
{
	size_t		index;
	size_t		jndex;
	char		*str;
	char		*str_cmp;
	long		diff[2];

	list_display_header();
	index = 0;
	while (g_strings[index])
	{
		str = g_strings[index];
		jndex = 0;
		while (g_strings[jndex])
		{
			str_cmp = g_strings[jndex];
			diff[0] = ft_strcmp(str, str_cmp);
			diff[1] = strcmp(str, str_cmp);
			list_display_result("ft_strcmp", (void *)diff[0],
											(void *)diff[1], LIST_AS_INT);
			jndex++;
		}
		index++;
	}
	printf("\n");
}
