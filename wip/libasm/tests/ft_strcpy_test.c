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
	static char *cpy_strs[] = {
		"Hello",
		"World",
		"From",
		"42",
		""
	};
	size_t		index;
	char		*src;
	char		*cpy;
	char		dst[1000];

	index = 0;
	while (index < 4)
	{
		src = cpy_strs[index];
		printf("--------------\n");
		printf("source    : %s (%p)\n", src, src);
		cpy = strcpy(dst, src);
		printf("strcpy    : %s (%p)\n", cpy, cpy);
		bzero(dst, 1000);
		cpy = ft_strcpy(dst, src);
		printf("ft_strcpy : %s (%p)\n", cpy, cpy);
		index++;
	}
}
