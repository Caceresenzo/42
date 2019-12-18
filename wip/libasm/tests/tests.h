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

# include "../libasm.h"

int		ft_atoi_base_2(char *str, char *base);
void	ft_list_sort_2(t_list **begin_list, int (*cmp)());

t_list	*ft_create_elem(void *data);
void	ft_list_push_back(t_list **begin_list, void *data);

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

#endif
