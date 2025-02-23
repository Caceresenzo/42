/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 21:29:24 by ecaceres          #+#    #+#             */
/*   Updated: 2021/03/06 21:29:24 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_H
# define LIST_H

# include <stdbool.h>
# include <string.h>

typedef struct s_list_node
{
	void				*data;
	struct s_list_node	*next;
}				t_list_node;

typedef struct s_list
{
	long		size;
	t_list_node	*first;
	t_list_node	*last;
}				t_list;

void			list_initialize(t_list *list);
t_list_node		*list_add(t_list *list, void *data);
void			list_delete(t_list *list, void (*del)(void*));
bool			list_remove(t_list *list, void *data, void (*del)(void*));
long			list_size(t_list *list);
long			list_size_filtered(t_list *list, bool (*predicate)(void*), bool negate);
void			list_for_each(t_list *list, void (*consumer)(void*));

void			list_node_initialize(t_list_node *node, void *data);
void			list_node_delete(t_list_node *node, void (*del)(void*));
t_list_node		*list_node_next(t_list_node *node);

#endif
