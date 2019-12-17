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

static char *tmp;

#define FT_STRDUP_EXPECT(str) do {  int diff=0;          \
        tmp = ft_strdup(str);                     \
        if (tmp == NULL || (diff = strcmp(str, tmp)) != 0) \
                printf("KO: [COMPARE]: DIFF %d\n%s:\nexpected: \"%s\"\ngot: \"%s\"\n", diff, "Hello", str, tmp); \
        else                                      \
                printf("ok");                           \
        free(tmp);                                \
} while (0);

void
	test_ft_strcmp(void)
{
	static char *cmp_strs[] = {
		"Hello",
		"World",
		"From",
		"42",
		"",
		"Biggy\x80 char",
		"Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed in malesuada purus. Etiam a scelerisque massa. Ut non euismod elit. Aliquam bibendum dolor mi, id fringilla tellus pulvinar eu. Fusce vel fermentum sem. Cras volutpat, eros eget rhoncus rhoncus, diam augue egestas dolor, vitae rutrum nisi felis sed purus. Mauris magna ex, mollis non suscipit eu, lacinia ac turpis. Phasellus ac tortor et lectus fermentum lobortis eu at mauris. Vestibulum sit amet posuere tortor, sit amet consequat amet."
	};
	size_t		index;
	size_t		jndex;
	char		*str;
	char		*str_cmp;
	size_t		length;

	index = 0;
	while (index < 7)
	{
		str = cmp_strs[index];
		jndex = 0;
		while (jndex < 7)
		{
			str_cmp = cmp_strs[jndex];
			int a = strcmp(str, str_cmp);
			int b = ft_strcmp(str, str_cmp);
			printf("--------------\n");
			printf("strcmp    : %d\n", a);
			printf("ft_strcmp : %d\n", b);
			printf("valid?    : %s\n", a == b ? "YES" : "NO");
			printf("cmp       : \"%s\" [%d] (%p) with \"%s\" (%p)\n", str, str[0], str, str_cmp, str_cmp);
			jndex++;
		}
		index++;
	}
	FT_STRDUP_EXPECT("Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed in malesuada purus. Etiam a scelerisque massa. Ut non euismod elit. Aliquam bibendum dolor mi, id fringilla tellus pulvinar eu. Fusce vel fermentum sem. Cras volutpat, eros eget rhoncus rhoncus, diam augue egestas dolor, vitae rutrum nisi felis sed purus. Mauris magna ex, mollis non suscipit eu, lacinia ac turpis. Phasellus ac tortor et lectus fermentum lobortis eu at mauris. Vestibulum sit amet posuere tortor, sit amet consequat amet.");
}
