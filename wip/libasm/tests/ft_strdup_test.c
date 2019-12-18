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
	farther(char *str)
{
	int i;

	i = 0;
	while (i != 200)
	{
		if (*str == '\e')
			write(1, "e", 1);
		else
			write(1, str, 1);
		str++;
		i++;
	}
}

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
		"",
		"Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed in malesuada purus. Etiam a scelerisque massa. Ut non euismod elit. Aliquam bibendum dolor mi, id fringilla tellus pulvinar eu. Fusce vel fermentum sem. Cras volutpat, eros eget rhoncus rhoncus, diam augue egestas dolor, vitae rutrum nisi felis sed purus. Mauris magna ex, mollis non suscipit eu, lacinia ac turpis. Phasellus ac tortor et lectus fermentum lobortis eu at mauris. Vestibulum sit amet posuere tortor, sit amet consequat amet."
	};
	size_t		index;
	char		*src;
	char		*duplicated;

	index = 0;
	while (index < 8)
	{
		src = dup_strs[index];
		printf("--------------\n");
		printf("\e[1msource    :\e[0m \e[96m%s\e[0m \e[95m(%p)\e[0m\n", src, src);
		duplicated = ft_strdup(src);
		printf("\e[1mft_strdup :\e[0m \e[96m%s\e[0m \e[95m(%p)\e[0m\n", duplicated, duplicated);
		printf("\e[1mfarther   :\e[0m \e[96m'");
		fflush(stdout);
		if (duplicated != NULL)
			farther(duplicated);
		printf("'\e[0m\n");
		if (duplicated != src)
			free(duplicated);
		index++;
	}
}
