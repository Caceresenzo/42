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
#include "../libasm.h"

void
	test_ft_strlen(void)
{
	static char *strs[] = {
		"Hello",
		"World",
		"From",
		"42",
		"",
		NULL
	};
	size_t		index;
	char		*str;
	size_t		length;

	strs[5] = calloc(UINT_MAX, sizeof(char));
	memset(strs[5], 'a', (long)UINT_MAX - 1);
	index = 0;
	while (index < 6)
	{
		str = strs[index];
		length = strlen(str);
		printf("--------------\n");
		printf("strlen    : %zu\n", length);
		printf("ft_strlen : %zu\n", ft_strlen(str));
		printf("string    : \"%s\"\n", length <= 50 ? str : "[...]");
		index++;
	}
}
