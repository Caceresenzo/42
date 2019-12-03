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
#include "../libasm.h"

void
	test_ft_strcmp(void)
{
	static char *cmp_strs[] = {
		"Hello",
		"World",
		"From",
		"42",
		"",
		"Biggy\x80 char"
	};
	size_t		index;
	size_t		jndex;
	char		*str;
	char		*str_cmp;
	size_t		length;

	index = 0;
	while (index < 6)
	{
		str = cmp_strs[index];
		jndex = 0;
		while (jndex < 6)
		{
			str_cmp = cmp_strs[jndex];
			printf("--------------\n");
			printf("strcmp    : %d\n", strcmp(str, str_cmp));
			printf("ft_strcmp : %d\n", ft_strcmp(str, str_cmp));
			printf("cmp       : \"%s\" [%d] (%d) with \"%s\" (%d)\n", str, str[0], (int) str, str_cmp, (int) str_cmp);
			jndex++;
		}
		index++;
	}
}
