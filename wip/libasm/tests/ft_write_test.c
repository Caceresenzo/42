/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_test.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 14:55:00 by ecaceres          #+#    #+#             */
/*   Updated: 2019/12/02 14:55:00 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

static void
	direct_print(char *message)
{
	printf("%s", message);
	fflush(stdout);
}

void
	test_ft_write(void)
{
	ssize_t		wrote[2];
	char		*str;
	size_t		index;

	list_display_header();
	index = 0;
	while ((str = g_strings[index]))
	{
		direct_print("ft_write:");
		wrote[0] = ft_write(0, str, strlen(str));
		direct_print("\nwrite:");
		wrote[1] = write(0, str, strlen(str));
		direct_print("\n");
		list_display_result("ft_write // returned", (void *)wrote[0],
											(void *)wrote[1], LIST_AS_INT);
		index++;
	}
	printf("\n");
}
