/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_remove_if.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 17:19:28 by ecaceres          #+#    #+#             */
/*   Updated: 2019/12/18 17:19:28 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tests.h"

void
	ft_list_remove_if_2(t_list **begin_list, void *data_ref,
						int (*cmp)(), void (*free_fct)(void *))
{
	t_list	*removed;

	if (begin_list == 0 || (*begin_list == 0))
		return ;
	if ((*cmp)((*begin_list)->data, data_ref) == 0)
	{
		removed = *begin_list;
		*begin_list = removed->next;
		(*free_fct)(removed->data);
		free(removed);
		ft_list_remove_if_2(begin_list, data_ref, cmp, free_fct);
	}
	else
		ft_list_remove_if_2(&(*begin_list)->next, data_ref, cmp, free_fct);
}
