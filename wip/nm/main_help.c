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

	ft_putstr_fd("Usage: ft_nm [option(s)] [file(s)]\n", fd);
	ft_putstr_fd(" List symbols in [file(s)] (a.out by default).\n", fd);
	ft_putstr_fd(" The options are:\n", fd);
	ft_putstr_fd("  -a, --debug-syms       Display debugger-only symbols\n", fd);
	ft_putstr_fd("  -g, --extern-only      Display only external symbols\n", fd);
	ft_putstr_fd("  -u, --undefined-only   Display only undefined symbols\n", fd);
	ft_putstr_fd("  -r, --reverse-sort     Reverse the sense of the sort\n", fd);
	ft_putstr_fd("  -p, --no-sort          Do not sort the symbols\n", fd);
	ft_putstr_fd("  -h, --help             Display this information\n", fd);
	ft_putstr_fd("  -V, --version          Display this program's version number\n", fd);
	ft_putstr_fd("\n", fd);
	ft_putstr_fd("ft_nm: supported targets: elf64 elf32\n", fd);

	return (is_err);
}

int
main_version()
{
	ft_putstr_fd("ft_nm " NM_VERSION "\n", STDOUT_FILENO);
	return (0);
}
