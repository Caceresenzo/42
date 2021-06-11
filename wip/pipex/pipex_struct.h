/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_struct.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 23:04:10 by ecaceres          #+#    #+#             */
/*   Updated: 2021/06/10 23:04:10 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_STRUCT_H
# define PIPEX_STRUCT_H

# include <unistd.h>

typedef struct s_pipex_params
{
	const char	*in;
	const char	*out;
	const char	**programs;
	int			program_count;
}	t_pipex_params;

typedef struct s_pipex_internal
{
	t_pipex_params	*params;
	int				in;
	int				out;
	int				(*pipes)[2];
	char			**paths;
	pid_t			*pids;
}	t_pipex_internal;

#endif
