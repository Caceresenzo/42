/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_struct.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 16:27:25 by ecaceres          #+#    #+#             */
/*   Updated: 2021/03/04 16:27:25 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OP_STRUCT_H
# define OP_STRUCT_H

# include "../libstack/stack.h"

typedef struct	s_op
{
	const char	*name;
	void		(*operation)(t_stack*, t_stack*);
}				t_op;

#endif
