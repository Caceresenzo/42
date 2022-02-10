/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arraylist_destroy.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 17:46:24 by ecaceres          #+#    #+#             */
/*   Updated: 2021/11/25 17:46:24 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "arraylist.h"

void
arraylist_destroy(t_arraylist *arraylist)
{
	if (!arraylist)
		return;

	free(arraylist->vector);
	free(arraylist);
}
