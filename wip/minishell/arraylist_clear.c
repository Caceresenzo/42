/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arraylist_clear.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 13:33:19 by ecaceres          #+#    #+#             */
/*   Updated: 2020/02/19 13:33:19 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arraylist.h"

int
	arraylist_clear(t_arrlst *alst, void (*free_fct)())
{
	while (alst->size != 0)
	{
		if (!arraylist_remove_at(alst, 0, free_fct))
			return (0);
	}
	return (1);
}
