/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_test.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 14:55:00 by ecaceres          #+#    #+#             */
/*   Updated: 2019/12/02 14:55:00 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

void
	test_ft_strdup(void)
{
	size_t		index;
	char		*src;
	char		*duplicate;

	list_display_header();
	index = 0;
	while ((src = g_strings[index]))
	{
		duplicate = ft_strdup(src);
		list_display_result("ft_strdup", src, duplicate, LIST_AS_STRING);
		free(duplicate);
		index++;
	}
	printf("\n");
}
