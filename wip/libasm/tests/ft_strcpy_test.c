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
#include "../libasm.h"

void
	test_ft_strcpy(void)
{
	static char *strs[] = {
		"Hello",
		"World",
		"From",
		"42",
		""
	};
	size_t		index;
	char		*src;
	char		dst[1000];

	index = 0;
	while (index < 5)
	{
		src = strs[index];
		printf("--------------\n");
		printf("strcpy    : %s\n", strcpy(dst, src));
		printf("ft_strcpy : %s\n", ft_strcpy(dst, src));
		index++;
	}
}
