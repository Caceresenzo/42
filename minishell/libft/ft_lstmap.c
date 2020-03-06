/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 17:43:36 by ecaceres          #+#    #+#             */
/*   Updated: 2019/11/05 17:43:36 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list
	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list *new_list;
	t_list *next_old;
	t_list *next_new;

	if (!lst || !(new_list = ft_lstnew((*f)(lst->content))))
		return (NULL);
	next_new = new_list;
	next_old = lst->next;
	while (1)
	{
		if (next_old == NULL)
			break ;
		if (!(next_new->next = ft_lstnew((*f)(next_old->content))))
		{
			ft_lstclear(&new_list, del);
			return (NULL);
		}
		next_new = next_new->next;
		next_old = next_old->next;
	}
	return (new_list);
}
