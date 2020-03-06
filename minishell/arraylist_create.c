/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arraylist_create.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 17:56:27 by ecaceres          #+#    #+#             */
/*   Updated: 2020/02/18 17:56:27 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arraylist.h"

t_arrlst
	*arraylist_create(size_t init_cap, void *cmp_method)
{
	t_arrlst	*alst;

	if (!(alst = (t_arrlst *)malloc(sizeof(t_arrlst))))
		return (NULL);
	arraylist_init(alst, cmp_method, 2);
	if (!arraylist_grow(alst, init_cap))
	{
		arraylist_destroy(alst);
		return (0);
	}
	return (alst);
}
