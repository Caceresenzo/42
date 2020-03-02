/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_input.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 15:33:08 by ecaceres          #+#    #+#             */
/*   Updated: 2020/02/18 15:33:08 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_mshell	*g_shell = NULL;
char		*g_saved = NULL;

static char
	*x_flush(char **sav, char *buffer)
{
	char	*new_line;
	char	*sub;
	char	*tmp;
	size_t	len;

	if (buffer != NULL)
	{
		*sav = ft_strjoin_free(*sav == NULL ? "" : *sav, buffer,
				*sav == NULL ? FT_STRJOIN_FREE_DONT : FT_STRJOIN_FREE_FIRST);
		if (*sav == NULL || ft_strlen(*sav) == 0)
		{
			free(*sav);
			*sav = NULL;
		}
	}
	if (*sav == NULL)
		return (NULL);
	if (!(new_line = ft_strchr(*sav, '\n')))
		return (NULL);
	len = new_line - *sav;
	sub = ft_substr(*sav, 0, len);
	tmp = (*sav)[len + 1] == '\0' ? NULL : ft_substr(*sav, len + 1, (size_t)-1);
	free(*sav);
	*sav = tmp;
	return (sub);
}

char
	*minishell_input_read(char **saved)
{
	ssize_t	avail;
	char	buff[8];
	char	*line;

	line = NULL;
	while (1)
	{
		if ((line = x_flush(saved, line == NULL ? NULL : buff)) != NULL)
			return (line);
		avail = read(IN, buff, sizeof(buff) - 1);
		buff[avail] = '\0';
		if (avail == -1)
			return (NULL);
		if (avail == 0)
		{
			ft_putchar_fd('\n', ERR);
			if (!*saved)
				return (NULL);
			line = *saved;
			*saved = NULL;
			return (line);
		}
		if ((line = x_flush(saved, buff)) != NULL)
			return (line);
	}
}

void
	minishell_input_loop(t_mshell *shell)
{
	char	*line;

	g_saved = NULL;
	while (1)
	{
		minishell_prompt_ask(shell, 0);
		line = minishell_input_read(&g_saved);
		if (line == NULL)
			break ;
		if (ft_strlen(line) != 0)
			minishell_evaluate(shell, line);
		free(line);
	}
	free(g_saved);
	g_saved = NULL;
}
