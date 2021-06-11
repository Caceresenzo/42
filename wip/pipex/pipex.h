/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 23:04:10 by ecaceres          #+#    #+#             */
/*   Updated: 2021/06/10 23:04:10 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "pipex_struct.h"
# include "libft/libft.h"

void		env_init(const char **envp);
const char	**env_get(void);
const char	*env_find(const char *key);
const char	*env_get_path(void);

char		*path_get(const char *bin);

bool		file_open(int *fd, const char *path, int flags);
bool		file_close(int *fd);
bool		file_test_read(const char *path);

int			pipex(t_pipex_params params);
bool		pipex_init(t_pipex_params *params, t_pipex_internal *internal);
int			pipex_destroy(t_pipex_internal *internal, int ret);
bool		pipex_open_pipes(t_pipex_internal *internal);
bool		pipex_find_files(t_pipex_internal *internal);
bool		pipex_exec(t_pipex_internal *internal);
void		pipex_debug(t_pipex_internal *internal);

#endif
