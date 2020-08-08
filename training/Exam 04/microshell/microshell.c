/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   microshell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 12:04:29 by ecaceres          #+#    #+#             */
/*   Updated: 2020/08/08 12:04:29 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "microshell.h"

char **g_envp = NULL;

size_t g_token_count = 0;
t_token *g_tokens = NULL;

size_t g_program_count = 1;
t_program *g_programs = NULL;

int
terminate(char *msg, bool asErr)
{
	if (msg)
	{
		ft_putstr(FD_ERR, msg);
		ft_putstr(FD_ERR, "\n");
	}

	for (size_t i = 0; i < g_program_count; ++i)
		free(g_programs[i].args);

	free(msg);
	free(g_tokens);
	free(g_programs);

	exit(asErr);

	return (0);
}

int
terminate_errno(char *origin)
{
	ft_putstr(FD_ERR, "microshell: ");
	if (origin)
	{
		ft_putstr(FD_ERR, origin);
		ft_putstr(FD_ERR, ": ");
	}
	ft_putstr(FD_ERR, strerror(errno));
	ft_putstr(FD_ERR, "\n");

	return (terminate(NULL, true));
}

int
main(int argc, char **argv, char **envp)
{
	g_envp = envp;

	if (argc == 1)
		return (0);

	g_tokens = malloc_zeros((g_token_count = argc - 1) * sizeof(t_token));

	/* Arguments to tokens. */
	for (int i = 1; i < argc; ++i)
	{
		t_token *tok = &(g_tokens[i - 1]);
		char *curr = tok->data = argv[i];

		tok->end = i == argc - 1;

		if (strcmp(";", curr) == 0)
			tok->type = TT_SEMICOLON;
		else if (strcmp("|", curr) == 0)
			tok->type = TT_PIPE;
		else
			tok->type = TT_STRING;

		if (tok->type != TT_STRING)
			g_program_count++;
	}

	g_programs = malloc_zeros(g_program_count * sizeof(t_program));

	/* Tokens to 'program' struct. */
	{
		size_t j = 0;

		for (size_t i = 0; i < g_program_count; ++i)
		{
			t_program *pr = &(g_programs[i]);

			size_t start = j++;

			t_token *tok = NULL;
			while (j < g_token_count)
			{
				tok = &(g_tokens[j++]);

				if (tok->type != TT_STRING)
				{
					pr->piped = tok->type == TT_PIPE;
					pr->semicoloned = tok->type == TT_SEMICOLON;
					break;
				}
			}

			size_t args_size = j - start - (tok != NULL && tok->type != TT_STRING);
			pr->args = malloc_zeros((args_size + 1) * sizeof(char*));

			for (size_t k = 0; k < args_size; ++k)
				pr->args[k] = g_tokens[start + k].data;

			pr->path = pr->args[0];
		}
	}

	//	/* Dump. */
//	for (size_t i = 0; i < g_program_count; ++i)
//	{
//		t_program *pr = &(g_programs[i]);
//
//		printf("\n\npath = %s\n", pr->path);
//		printf("piped = %s\n", pr->piped ? "true" : "false");
//		printf("semicoloned = %s\n", pr->semicoloned ? "true" : "false");
//		for (size_t j = 0; pr->args[j]; ++j)
//			printf("arg[%zu] = %s\n", j, pr->args[j]);
//	}

	int pipe_fds[2] = { 0, 0 };
	int fd_in = 0;

	/* Execution. */
	for (size_t i = 0; i < g_program_count; ++i)
	{
		t_program *pr = &(g_programs[i]);

		pipe(pipe_fds);

		if ((pr->pid = fork()) == -1)
			return (terminate_errno("fork"));
		else if (pr->pid == 0)
		{
			dup2(fd_in, FD_IN);
			if (pr->piped)
				dup2(pipe_fds[1], FD_OUT);

			close(pipe_fds[0]);

			if (execve(pr->path, pr->args, g_envp) == -1)
				return (terminate_errno("execve"));
		}
		else
		{
			if (pr->semicoloned || i == g_program_count - 1)
			{
//				ft_putstr(FD_ERR, strcat(strcat(strdup("waiting: "), pr->path), "\n"));
				waitpid(pr->pid, NULL, 0);
				close(pipe_fds[0]);
				fd_in = 0;
			}
			else
				fd_in = pipe_fds[0];
			close(pipe_fds[1]);
		}
	}

	/* Just to be sure. */
	for (size_t i = 0; i < g_program_count; ++i)
		waitpid(g_programs[i].pid, NULL, 0);

	return (terminate(NULL, false));
}
