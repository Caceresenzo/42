/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_serv.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 14:17:38 by ecaceres          #+#    #+#             */
/*   Updated: 2021/03/29 14:17:38 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_SERV_H
# define MINI_SERV_H

typedef struct s_list
{
	void *data;
	struct s_list *next;
} t_list;

typedef struct
{
	int use;
	char *data;
	int len;
} t_instanced_string;

typedef struct
{
	int id;
	int fd;
	t_list *messages;
	int send_up_to;
	char *buffer;
} t_client;

t_list*
list_add(t_list **lst, void *data);

void
list_clear(t_list **lst, void (*del)(void*));

void
list_delete_first(t_list **lst, void *data, void (*del)(void*));

t_instanced_string*
istr_wrap(char *cstr);

t_instanced_string*
istr_use(t_instanced_string *str);

void
istr_unuse(t_instanced_string *str);

void
istr_unuse_v(void *str);

#endif
