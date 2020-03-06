/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 17:39:25 by ecaceres          #+#    #+#             */
/*   Updated: 2019/11/05 17:39:25 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void
	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*next;

	if (lst != NULL)
	{
		next = lst;
		while (1)
		{
			(*f)(next->content);
			next = next->next;
			if (next == NULL)
				return ;
		}
	}
}
