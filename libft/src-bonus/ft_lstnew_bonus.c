/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 15:37:20 by ecaceres          #+#    #+#             */
/*   Updated: 2019/11/05 15:37:20 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_bonus.h"

t_list		*ft_lstnew(void *content)
{
	t_list *list;

	CHECK_MALLOC(list, sizeof(list));
	list->content = content;
	list->next = NULL;
	return (list);
}
