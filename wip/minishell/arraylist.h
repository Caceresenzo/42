/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arraylist.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 17:56:38 by ecaceres          #+#    #+#             */
/*   Updated: 2020/02/18 17:56:38 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARRAYLIST_H
# define ARRAYLIST_H

# include "libft/libft.h"

typedef struct		s_arrlst
{
	int				kind;
	void			**items;
	size_t			size;
	size_t			capacity;
	int				(*cmp_method)(void *, void *);
	size_t			grow_factor;
}					t_arrlst;

t_arrlst			*arraylist_create(size_t init_cap, void *cmp_method);
void				arraylist_init(t_arrlst *alst, void *cmp, size_t g_fac);

void				arraylist_destroy_items(t_arrlst *alst);
void				arraylist_destroy(t_arrlst *alst);

int					arraylist_insert(t_arrlst *alst, size_t pos, void *ptr);

void				*arraylist_get(t_arrlst *alst, void *ptr);

int					arraylist_add(t_arrlst *alst, void *ptr);
int					arraylist_add_char(t_arrlst *alst, char chr);

int					arraylist_add_all(t_arrlst *dstlst, t_arrlst *srclst);

size_t				arraylist_size(t_arrlst *alst);

int					arraylist_grow(t_arrlst *alst, size_t n);

ssize_t				arraylist_index_of(t_arrlst *alst, void *ptr);

int					arraylist_remove(t_arrlst *alst, void *ptr, void (*del)());
int					arraylist_remove_at(t_arrlst *l, size_t pos, void (*del)());
int					arraylist_clear(t_arrlst *alst, void (*del)());

t_arrlst			*arraylist_duplicate(t_arrlst *alst);

int					arraylist_sort(t_arrlst *alst, int (*other_cmp)());

#endif
