/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arraylist_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 18:58:59 by ecaceres          #+#    #+#             */
/*   Updated: 2020/02/18 18:58:59 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arraylist.h"

void
	arraylist_init(t_arrlst *alst, void *cmp_method, size_t grow_factor)
{
	ft_memset(alst, 0, sizeof(t_arrlst));
	alst->cmp_method = cmp_method;
	alst->grow_factor = grow_factor;
}
