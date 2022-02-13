/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_help.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 18:17:59 by ecaceres          #+#    #+#             */
/*   Updated: 2022/02/13 18:17:59 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdio.h>

#include "nm.h"

int
main_help(bool is_err)
{
	int fd = is_err ? STDERR_FILENO : STDOUT_FILENO;

	dprintf(fd, "Usage: ft_nm [option(s)] [file(s)]\n");
	dprintf(fd, " List symbols in [file(s)] (a.out by default).\n");
	dprintf(fd, " The options are:\n");
	dprintf(fd, "  -a, --debug-syms       Display debugger-only symbols\n");
	dprintf(fd, "  -g, --extern-only      Display only external symbols\n");
	dprintf(fd, "  -u, --undefined-only   Display only undefined symbols\n");
	dprintf(fd, "  -r, --reverse-sort     Reverse the sense of the sort\n");
	dprintf(fd, "  -p, --no-sort          Do not sort the symbols\n");
	dprintf(fd, "  -h, --help             Display this information\n");
	dprintf(fd, "  -V, --version          Display this program's version number\n");
	dprintf(fd, "\n");
	dprintf(fd, "ft_nm: supported targets: elf64 elf32\n");

	return (is_err);
}

int
main_version()
{
	printf("ft_nm %s\n", NM_VERSION);
	return (0);
}
