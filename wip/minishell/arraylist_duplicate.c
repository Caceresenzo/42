/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arraylist_duplicate.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 13:33:19 by ecaceres          #+#    #+#             */
/*   Updated: 2020/02/19 13:33:19 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arraylist.h"

t_arrlst
	*arraylist_duplicate(t_arrlst *alst)
{
	t_arrlst	*dup;

	if (alst == NULL)
		return (NULL);
	if ((dup = arraylist_create(1, alst->cmp_method)))
	{
		arraylist_add_all(dup, alst);
		dup->grow_factor = alst->grow_factor;
	}
	return (dup);
}
