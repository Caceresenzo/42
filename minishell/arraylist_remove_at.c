/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arraylist_remove_at.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 13:33:19 by ecaceres          #+#    #+#             */
/*   Updated: 2020/02/19 13:33:19 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arraylist.h"

int
	arraylist_remove_at(t_arrlst *alst, size_t pos, void (*free_fct)())
{
	if (alst == NULL || alst->size == 0 || pos >= alst->size)
		return (0);
	if (free_fct != NULL)
		(*free_fct)(alst->items[pos]);
	ft_memmove(alst->items + pos, alst->items + pos + 1,
				(alst->size - pos) * sizeof(void *));
	alst->size -= 1;
	return (1);
}
