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

#include "tests.h"

void
	notify(char c)
{
	if (!NOTIFY)
		return ;
	printf("\t\t\t\t\t\t\t\t\tnotified %c (%d)\n", c, c);
	fflush(stdout);
}

void
	notifys(char *str)
{
	if (!NOTIFY)
		return ;
	printf("\t\t\t\t\t\t\t\t\tnotified %s (%p)\n", str, str);
	fflush(stdout);
}

int
	main(void)
{
	if (NOTIFY)
	{
		notify('0');
		notifys("hello");
		test_ft_strlen();
		test_ft_strcpy();
		test_ft_strcmp();
		test_ft_write();
		test_ft_read();
		test_ft_strdup();
	}
	else
		write(1, ft_strdup("This is very long"), strlen("This is very long"));
}
