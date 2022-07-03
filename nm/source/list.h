/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 18:38:33 by ecaceres          #+#    #+#             */
/*   Updated: 2022/02/13 18:38:33 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_H
# define LIST_H

# include <stdlib.h>
# include <stdbool.h>
# include "ft.h"

typedef struct s_list_node
{
	void *data;
	struct s_list_node *next;
} t_list_node;

// @formatter:off
typedef void (*t_list_node_consumer)(void*);
typedef int (*t_list_node_compare)(const void*, const void*);
// @formatter:on

typedef struct
{
	long size;
	t_list_node *first;
	t_list_node *last;
} t_list;

void
list_initialize(t_list *list);

t_list_node*
list_add(t_list *list, void *data);

void
list_delete(t_list *list, t_list_node_consumer del);

long
list_size(t_list *list);

void
list_for_each(t_list *list, t_list_node_consumer consumer);

void
list_node_initialize(t_list_node *node, void *data);

void
list_node_delete(t_list_node *node, t_list_node_consumer del);

t_list_node*
list_node_next(t_list_node *node);

bool
list_sort(t_list *list, t_list_node_compare comparator);

void
list_reverse(t_list *list);

#endif
