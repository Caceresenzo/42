/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 13:33:23 by ecaceres          #+#    #+#             */
/*   Updated: 2019/12/03 13:33:23 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libasm.h"
#include "tests.h"
#include "../debug/notifier.h"

char *g_strings[] = {
	"This is very very very long",
	"This is shorter",
	"Hello",
	"World",
	"From",
	"Biggy\250Char",
	"42",
	"",
	"Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed in"
	"malesuada purus. Etiam a scelerisque massa. Ut non euismod elit."
	"Aliquam bibendum dolor mi, id fringilla tellus pulvinar eu. Fusce"
	"vel fermentum sem. Cras volutpat, eros eget rhoncus rhoncus, diam"
	"augue egestas dolor, vitae rutrum nisi felis sed purus. Mauris magna"
	"ex, mollis non suscipit eu, lacinia ac turpis. Phasellus ac tortor et"
	"lectus fermentum lobortis eu at mauris. Vestibulum sit amet posuere"
	"tortor, sit amet consequat amet.",
	NULL
};

int
	main(void)
{
	if (NOTIFY)
	{
		test_ft_strlen();
		test_ft_strcpy();
		test_ft_strcmp();
		test_ft_write();
		test_ft_read();
		test_ft_strdup();
		test_ft_atoi_base();
		test_ft_list_push_front();
		test_ft_list_size();
		test_ft_list_sort();
		test_ft_list_remove_if();
	}
	else
	{
		write(1, ft_strdup("This is very long"), strlen("This is very long"));
	}
}
