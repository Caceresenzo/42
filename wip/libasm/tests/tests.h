/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 13:33:31 by ecaceres          #+#    #+#             */
/*   Updated: 2019/12/03 13:33:31 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTS_H
# define TESTS_H

# include <stdio.h>
# include <limits.h>
# include <string.h>
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>

# include "../libasm.h"
# include "utils/libft.h"

# define LIST_AS_STRING 1
# define LIST_AS_INT 2
# define LIST_AS_INT_FROM_PTR 3

# ifndef MORE_DEBUG
#  define MORE_DEBUG 0
# endif

extern char	*g_strings[];

int		ft_atoi_base_2(char *str, char *base);
void	ft_list_push_front_2(t_list **begin_list, void *data);
void	ft_list_sort_2(t_list **begin_list, int (*cmp)());
void	ft_list_remove_if_2(t_list **begin_list, void *data_ref,
							int (*cmp)(), void (*free_fct)(void *));

t_list	*ft_create_elem(void *data);
void	ft_list_push_back(t_list **begin_list, void *data);

void	list_generate(t_list **list);
void	list_generate_sized(t_list **list, size_t size);
void	list_display_header(void);
void	list_display_content(char *name, t_list **list, int as);
void	list_display_result(char *name, void *a, void *b, int as);

void	test_ft_strlen(void);
void	test_ft_strcpy(void);
void	test_ft_strcmp(void);
void	test_ft_write(void);
void	test_ft_read(void);
void	test_ft_strdup(void);

void	test_ft_atoi_base(void);
void	test_ft_list_push_front(void);
void	test_ft_list_size(void);
void	test_ft_list_sort(void);
void	test_ft_list_remove_if(void);

#endif
