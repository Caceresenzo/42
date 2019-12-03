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
	static char *dup_strs[] = {
		"This is very very very long",
		"This is shorter",
		"Hello",
		"World",
		"From",
		"42",
		""
	};
	size_t		index;
	char		*src;
	char		*duplicated;

	index = 0;
	while (index < 5)
	{
		src = dup_strs[index];
		printf("--------------\n");
		printf("source    : %s (%p)\n", src, src);
		duplicated = ft_strdup(src);
		printf("ft_strdup : %s (%p)\n", duplicated, duplicated);
		free(duplicated);
		index++;
	}
}
