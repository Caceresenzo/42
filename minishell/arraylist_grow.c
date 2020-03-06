/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arraylist_grow.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 18:13:37 by ecaceres          #+#    #+#             */
/*   Updated: 2020/02/18 18:13:37 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arraylist.h"

int
	arraylist_grow(t_arrlst *alst, size_t n)
{
	size_t	new_cap;
	void	**old_items;

	if (alst == NULL || n == 0)
		return (0);
	new_cap = alst->size + n;
	if (new_cap <= alst->capacity)
		return (1);
	new_cap = alst->size + (n * alst->grow_factor);
	old_items = alst->items;
	if (!(alst->items = (void **)malloc(new_cap * sizeof(void *))))
		return (0);
	ft_bzero(alst->items, new_cap * sizeof(void *));
	if (old_items != NULL)
		ft_memcpy(alst->items, old_items, alst->size * sizeof(void *));
	free(old_items);
	alst->capacity = new_cap;
	return (1);
}
