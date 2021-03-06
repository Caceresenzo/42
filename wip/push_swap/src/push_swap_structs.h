/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_strucs.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 11:16:40 by ecaceres          #+#    #+#             */
/*   Updated: 2021/03/04 11:16:40 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_STRUCS_H
# define PUSH_SWAP_STRUCS_H

# include "../liblist/list.h"
# include "../libstack/stack.h"

typedef struct	s_op
{
	const char	*name;
	void		(*operation)(t_stack*, t_stack*);
}				t_op;

typedef struct	s_result
{
	t_list						operations;
	const struct s_algorithm	*algorithm;
	long						count;
	bool						success;
}				t_result;

typedef struct	s_algorithm
{
	const char *name;
	bool		(*run)(t_result*, t_stack*, t_stack*);
}				t_algorithm;

#endif
