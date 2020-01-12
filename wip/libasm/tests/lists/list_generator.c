/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_generator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 19:16:17 by ecaceres          #+#    #+#             */
/*   Updated: 2019/08/05 19:16:20 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tests.h"

void
	list_generate(t_list **list)
{
	list_generate_sized(list, 26);
}

void
	list_generate_sized(t_list **list, size_t size)
{
	int		index;
	int		*duplicate;

	index = 0;
	while (index < size)
	{
		duplicate = malloc(sizeof(int));
		*duplicate = index;
		ft_list_push_back(&(list[0]), duplicate);
		ft_list_push_back(&(list[1]), ft_memdup(duplicate, sizeof(int)));
		index++;
	}
}
