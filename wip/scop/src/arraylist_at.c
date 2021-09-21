/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arraylist_at.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 11:38:10 by ecaceres          #+#    #+#             */
/*   Updated: 2021/09/21 11:38:10 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arraylist.h"

void*
arraylist_at(t_arraylist *arraylist, ssize_t index)
{
	return (((char*)arraylist->vector) + (arraylist->type_size * index));
}
