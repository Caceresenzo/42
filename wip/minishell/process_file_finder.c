/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_file_finder.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 17:18:56 by ecaceres          #+#    #+#             */
/*   Updated: 2020/02/20 17:18:56 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char
	*try_path(char *path, t_process *process, int with_build)
{
	struct stat	stats;
	DIR			*dir;

	if (path == NULL)
		return (NULL);
	if (with_build)
		process->filepath = ft_strjoin3(path, "/", process->name);
	else
		process->filepath = ft_strjoin(path, process->name);
	if (stat(process->filepath, &stats) != -1)
	{
		dir = opendir(process->filepath);
		if (dir == NULL)
			return (process->filepath);
		closedir(dir);
		process->is_dir = 1;
		return (process->filepath);
	}
	free(process->filepath);
	process->filepath = NULL;
	return (NULL);
}

static void
	search(t_process *process, char **paths)
{
	size_t	index;
	size_t	size;
	char	*cwd;

	if (process->name[0] == '/')
		try_path("/", process, 0);
	else if (ft_strchr(process->name, '/') != NULL)
	{
		try_path((cwd = getcwd(NULL, 0)), process, 1);
		free(cwd);
	}
	else
	{
		if (!paths)
			return ;
		size = ft_split_length(paths);
		index = 0;
		while (index < size)
		{
			if (try_path(paths[index], process, 1))
				return ;
			index++;
		}
	}
}

int
	process_find_path(t_process *process)
{
	char		**paths;
	t_env_var	*var;

	paths = NULL;
	if ((var = env_get_by_name("PATH")) != NULL)
		paths = ft_split(var->value, ':');
	search(process, paths);
	ft_split_free(&paths);
	return (process->filepath != NULL);
}
