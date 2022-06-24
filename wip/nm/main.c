/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 18:17:59 by ecaceres          #+#    #+#             */
/*   Updated: 2022/02/13 18:17:59 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <elf.h>
#include <errno.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/errno.h>
#include <sys/fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/unistd.h>
#include <unistd.h>

#include "ft.h"
#include "list.h"
#include "nm.h"

#ifndef SAFE_BYTE
# define SAFE_BYTE 32
#endif

#if SAFE_BYTE < 0
# error "SAFE_BYTE is negative"
#endif

static void
print_message(int fd, const char *file, const char *text)
{
	ft_putstr_fd("ft_nm: ", fd);
	ft_putstr_fd(file, fd);
	ft_putstr_fd(": ", fd);
	ft_putstr_fd(text, fd);
	ft_putstr_fd("\n", fd);
}

static void
print_message_errno(int fd, const char *file)
{
	print_message(fd, file, strerror(errno));
}

static void
print_invalid_option_word(const char *word)
{
	ft_putstr_fd("ft_nm: unrecognized option '--", STDERR_FILENO);
	ft_putstr_fd(word, STDERR_FILENO);
	ft_putstr_fd("'\n", STDERR_FILENO);
}

static void
print_invalid_option_letter(char letter)
{
	ft_putstr_fd("ft_nm: invalid option -- '", STDERR_FILENO);
	ft_putchar_fd(letter, STDERR_FILENO);
	ft_putstr_fd("'\n", STDERR_FILENO);
}

t_symbol*
main_nm_process(t_elf *elf, t_elf_symbol *elf_symbol, t_elf_section_header *section_strtab, t_elf_section_header *symbol_strtab)
{
	t_elf_address value = elf_symbol_get_value(elf, elf_symbol);

	if (elf->nm->flags.include_all && elf_symbol_get_section_info_type(elf, elf_symbol) == STT_SECTION)
	{
		char letter = elf_symbol_decode(elf, elf_symbol);
		if (!letter)
			return (NULL);

		t_elf_section_header *header = elf_sections_at(elf, elf_symbol_get_section_index(elf, elf_symbol));

		const char *name = NULL;
		if (header)
			name = elf_string_get(elf, section_strtab, elf_section_get_name(elf, header));

		return (symbol_create(value, true, name, letter));
	}

	t_elf_section section_index = elf_symbol_get_section_index(elf, elf_symbol);

	if (elf->nm->flags.only_undefined && section_index != SHN_UNDEF)
		return (NULL);

	if (elf->nm->flags.only_extern && !elf_symbol_is_external(elf, elf_symbol))
		return (NULL);

	t_elf_word name_offset = elf_symbol_get_name(elf, elf_symbol);
	if (!name_offset && elf_symbol_get_section_index(elf, elf_symbol) != SHN_ABS)
		return (NULL);

	const char *name = elf_string_get(elf, symbol_strtab, name_offset);

	char letter = elf_symbol_decode(elf, elf_symbol);
	if (!letter)
		return (NULL);

	/* from: https://stackoverflow.com/a/55127171/7292958 */
	if (letter == 'c' || letter == 'C')
		value = elf_symbol_get_size(elf, elf_symbol);

	if (!elf->nm->flags.include_all && letter == 'a')
		return (NULL);

	bool has_address = section_index != SHN_UNDEF;
	return (symbol_create(value, has_address, name, letter));
}

t_message
main_nm(t_nm *nm, const char *file, bool multiple, char *ptr, struct stat *statbuf)
{
	if (statbuf->st_size < EI_NIDENT)
		return (message_error("invalid header"));

	if (ft_memcmp(ptr, ELFMAG, 4) != 0)
		return (message_error("invalid magic"));

	bool is32 = ptr[EI_CLASS] == ELFCLASS32;
	bool is64 = ptr[EI_CLASS] == ELFCLASS64;

	if (!is32 && !is64)
		return (message_error("invalid architecture"));

	t_elf elf;
	ft_bzero(&elf, sizeof(t_elf));

	elf.ptr = ptr;
	elf.size = statbuf->st_size;
	elf.x32 = is32;
	elf.x64 = is64;
	elf.nm = nm;

	if (elf.size < elf_header_sizeof(&elf))
		return (message_error("invalid header size"));

	if (multiple)
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		ft_putstr_fd(file, STDOUT_FILENO);
		ft_putstr_fd(":\n", STDOUT_FILENO);
	}

	t_elf_section_header *symbol_section = elf_sections_find_by_type(&elf, SHT_SYMTAB);
	if (!symbol_section)
		return (message_simple("no symbols"));

	t_elf_word symbol_section_size = elf_section_get_size(&elf, symbol_section);
	t_elf_word symbol_section_entity_size = elf_section_get_entity_size(&elf, symbol_section);
	if (!symbol_section_size || !symbol_section_entity_size)
		return (message_simple("0 symbol"));

	t_elf_word symbol_count = symbol_section_size / symbol_section_entity_size;

	t_elf_symbol *elf_symbol = elf_symbol_from(&elf, symbol_section);
	if (!elf_symbol)
		return (message_error("invalid symbol offset"));

	t_elf_section_header *symbol_strtab = elf_sections_at(&elf, elf_section_get_link(&elf, symbol_section));
	if (elf_section_get_type(&elf, symbol_strtab) != SHT_STRTAB)
		symbol_strtab = NULL;

	t_elf_section_header *section_strtab = elf_sections_at(&elf, elf_header_get_section_string_index(&elf));
	if (elf_section_get_type(&elf, section_strtab) != SHT_STRTAB)
		section_strtab = NULL;

	t_list list;
	list_initialize(&list);

	while (symbol_count--)
	{
		t_symbol *symbol = main_nm_process(&elf, elf_symbol, section_strtab, symbol_strtab);
		if (symbol)
			list_add(&list, symbol);

		elf_symbol = elf_symbol_next(&elf, elf_symbol);
	}

	t_sort sort = nm->flags.sort;
	if (sort == SORT_NAME)
		list_sort(&list, &symbol_list_compare_name);
	else if (sort == SORT_NUMERIC)
		list_sort(&list, &symbol_list_compare_numeric);

	bool sort_reverse = nm->flags.sort_reverse;
	if (sort_reverse && sort != SORT_NONE)
		list_reverse(&list);

	if (elf.x32)
		list_for_each(&list, (t_list_node_consumer)&symbol_print_x32);
	else if (elf.x64)
		list_for_each(&list, (t_list_node_consumer)&symbol_print_x64);

	list_delete(&list, &free);

	return (message_none());
}

int
main_file(t_nm *nm, const char *file, bool multiple)
{
	struct stat statbuf;

	int fd = open(file, 0);
	if (fd == -1)
	{
		print_message_errno(STDERR_FILENO, file);
		return (1);
	}

	int ret = fstat(fd, &statbuf);
	if (ret == -1)
	{
		print_message_errno(STDERR_FILENO, file);
		close(fd);
		return (1);
	}

	if (!S_ISREG(statbuf.st_mode))
	{
		print_message(STDERR_FILENO, file, "not a regular file");
		close(fd);
		return (1);
	}

	char *ptr = mmap(NULL, statbuf.st_size + SAFE_BYTE, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
	if (!ptr)
	{
		print_message_errno(STDERR_FILENO, file);
		close(fd);
		return (1);
	}

	if (SAFE_BYTE)
		ft_memset(ptr + statbuf.st_size, '0', SAFE_BYTE);

	t_message message = main_nm(nm, file, multiple, ptr, &statbuf);
	if (message.text)
	{
		if (message.error)
			print_message(STDERR_FILENO, file, message.text);
		else
			print_message(STDOUT_FILENO, file, message.text);
	}

	munmap(ptr, statbuf.st_size);
	close(fd);
	return (message.error);
}

int
main(int argc, char **argv)
{
	t_nm nm;
	ft_bzero(&nm, sizeof(nm));

	int file_index = -1;
	if (!flags_parse(&nm.flags, argc, argv, &file_index))
	{
		if (nm.flags.unknown_word)
			print_invalid_option_word(nm.flags.unknown_word);
		else
			print_invalid_option_letter(nm.flags.unknown_letter);

		return (main_help(true));
	}

	if (nm.flags.help)
		return (main_help(false));

	if (nm.flags.version)
		return (main_version());

	if (file_index == -1)
		return (main_file(&nm, "a.out", false));
	else
	{
		bool multiple = argc > file_index + 1;

		int ret = 0;
		for (int index = file_index; index < argc; index++)
			ret |= main_file(&nm, argv[index], multiple);

		return (ret);
	}
}
