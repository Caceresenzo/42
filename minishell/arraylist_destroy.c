/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arraylist_destroy.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 18:27:16 by ecaceres          #+#    #+#             */
/*   Updated: 2020/02/18 18:27:16 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arraylist.h"

void
	arraylist_destroy_items(t_arrlst *alst)
{
	if (alst != NULL)
	{
		free(alst->items);
		alst->size = 0;
		alst->capacity = 0;
	}
}

void
	arraylist_destroy(t_arrlst *alst)
{
	arraylist_destroy_items(alst);
	free(alst);
}
