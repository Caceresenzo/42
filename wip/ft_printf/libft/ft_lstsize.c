/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 16:02:29 by ecaceres          #+#    #+#             */
/*   Updated: 2019/11/05 16:02:29 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int
	ft_lstsize(t_list *lst)
{
	int		size;
	t_list	*next;

	size = 0;
	next = lst;
	while (next != NULL)
	{
		next = next->next;
		size++;
	}
	return (size);
}
