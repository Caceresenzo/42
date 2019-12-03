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
#include "../libasm.h"

void
	test_ft_write(void)
{
	static char *len_strs[] = {
		"Hello",
		"World",
		"From",
		"42",
		""
	};
	size_t		index;
	char		*str;
	size_t		length;

	index = 0;
	while (index < 5)
	{
		str = len_strs[index];
		length = strlen(str);
		printf("--------------\n");
		printf("\nwrite     : %zu\n", write(1, str, length));
		printf("\nft_write  : %zu\n", ft_write(1, str, length));
		printf("string    : \"%s\"\n", str);
		index++;
	}
}
