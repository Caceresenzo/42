/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_size_test.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 14:55:00 by ecaceres          #+#    #+#             */
/*   Updated: 2019/12/02 14:55:00 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

void
	test_ft_list_size(void)
{
	t_list	*lst;
	size_t	index;

	lst = NULL;
	index = 0;
	while (index < 10000)
	{
		ft_list_push_front(&lst, "Hello");
		if ((index + 1) % 100 == 0)
			printf("size = %d\n", ft_list_size(lst));
		index++;
	}
}
