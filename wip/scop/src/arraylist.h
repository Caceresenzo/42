/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arraylist.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 11:26:41 by ecaceres          #+#    #+#             */
/*   Updated: 2021/09/21 11:26:41 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARRAYLIST_H
# define ARRAYLIST_H

# include <stdbool.h>
# include <unistd.h>

typedef struct s_arraylist
{
	size_t size;
	size_t capacity;
	size_t type_size;
	void *vector;
} t_arraylist;

bool
arraylist_initialize(t_arraylist *arraylist, size_t initial_capacity, size_t type_size);

bool
arraylist_grow(t_arraylist *arraylist, size_t to_capacity);

bool
arraylist_grow_auto(t_arraylist *arraylist);

void*
arraylist_add_to(t_arraylist *arraylist);

void*
arraylist_at(t_arraylist *arraylist, ssize_t index);

void
arraylist_destroy(t_arraylist *arraylist);

#endif
