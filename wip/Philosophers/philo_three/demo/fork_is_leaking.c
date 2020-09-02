/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_is_leaking.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/02 14:46:44 by ecaceres          #+#    #+#             */
/*   Updated: 2020/09/02 14:46:44 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void
	ft_putstr(char *str)
{
	char *end;

	end = str;
	while (*end)
		end++;
	write(1, str, end - str);
}

int
	main(void)
{
	pid_t pid;

	if ((pid = fork()) == -1)
		ft_putstr("failed to fork\n");
	else if (pid)
	{
		ft_putstr("parent is up\n");
		while (1)
			;
	}
	else
	{
		ft_putstr("child is up\n");
		while (1)
			;
	}
}
