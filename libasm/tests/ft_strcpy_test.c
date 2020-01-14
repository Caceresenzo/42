/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy_test.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 14:55:00 by ecaceres          #+#    #+#             */
/*   Updated: 2019/12/02 14:55:00 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

void
	test_ft_strcpy(void)
{
	size_t		index;
	char		*src;
	char		*cpy[2];
	char		dst[2][1000];

	list_display_header();
	index = 0;
	while ((src = g_strings[index]))
	{
		bzero(dst[0], 500);
		bzero(dst[1], 500);
		cpy[0] = ft_strcpy(dst[0], src);
		cpy[1] = strcpy(dst[1], src);
		list_display_result("ft_strcpy", (void *)cpy[0],
										(void *)cpy[1], LIST_AS_STRING);
		index++;
	}
	printf("\n");
}
