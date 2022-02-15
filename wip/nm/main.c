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
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/fcntl.h>
#include <sys/errno.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/unistd.h>

#include "list.h"
#include "nm.h"

t_symbol*
main_nm_process(t_elf *elf, t_elf_symbol *elf_symbol, t_elf_section_header *section_strtab, t_elf_section_header *symbol_strtab)
{
	t_elf_address address = elf_symbol_get_value(elf, elf_symbol);

	if (elf->nm->flags.include_all && elf_symbol_get_section_info_type(elf, elf_symbol) == STT_SECTION)
	{
		char letter = elf_symbol_decode(elf, elf_symbol);
		if (!letter)
			return (NULL);

		t_elf_section_header *header = elf_sections_at(elf, elf_symbol_get_section_index(elf, elf_symbol));

		const char *name = NULL;
		if (header)
			name = elf_string_get(elf, section_strtab, elf_section_get_name(elf, header));

		return (symbol_create(address, true, name, letter));
	}

	t_elf_section section_index = elf_symbol_get_section_index(elf, elf_symbol);

	if (elf->nm->flags.only_undefined && section_index != SHN_UNDEF)
		return (NULL);

	if (elf->nm->flags.only_extern && !elf_symbol_is_external(elf, elf_symbol))
		return (NULL);

	bool has_address = address != 0;
	if (section_index == SHN_ABS)
	{
		has_address = true;

		if (!elf->nm->flags.include_all)
			return (NULL);
	}

	t_elf_word name_offset = elf_symbol_get_name(elf, elf_symbol);
	if (!name_offset && elf_symbol_get_section_index(elf, elf_symbol) != SHN_ABS)
		return (NULL);

	const char *name = elf_string_get(elf, symbol_strtab, name_offset);

	char letter = elf_symbol_decode(elf, elf_symbol);
	if (!letter)
		return (NULL);

//

//	if (strcmp("__init_array_end", name) && strcmp("__do_global_dtors_aux_fini_array_entry", name) && strcmp("main", name))
//		return (NULL);
//	printf("letter=%c\n", letter);
//	printf("only_extern=%d\n", elf->nm->flags.only_extern);
//	printf("info_bind=%d\n", elf_symbol_get_section_info_bind(elf, elf_symbol));
//	printf("info_type=%d\n", elf_symbol_get_section_info_type(elf, elf_symbol));
//	printf("visibility=%d\n", elf_symbol_get_section_other_visibility(elf, elf_symbol));
//	printf("size=%d\n", elf_symbol_get_size(elf, elf_symbol));
//	printf("section_index=%d\n", section_index);
//	printf("name=%s\n", name);
//	printf("\n");
//

	return (symbol_create(address, has_address, name, letter));
}

const char*
main_nm(t_nm *nm, const char *file, char *ptr, struct stat *statbuf)
{
	if (statbuf->st_size < EI_NIDENT)
		return ("invalid header");

	if (memcmp(ptr, ELFMAG, 4) != 0)
		return ("invalid magic");

	bool is32 = ptr[EI_CLASS] == ELFCLASS32;
	bool is64 = ptr[EI_CLASS] == ELFCLASS64;

	if (!is32 && !is64)
		return ("invalid architecture");

	t_elf elf;
	bzero(&elf, sizeof(t_elf));

	elf.ptr = ptr;
	elf.size = statbuf->st_size;
	elf.x32 = is32;
	elf.x64 = is64;
	elf.nm = nm;

	if (elf.size < elf_header_sizeof(&elf))
		return ("invalid header size");

	t_elf_section_header *symbol_section = elf_sections_find_by_type(&elf, SHT_SYMTAB);
	if (!symbol_section)
		return ("no symbols found");

	t_elf_word symbol_section_size = elf_section_get_size(&elf, symbol_section);
	t_elf_word symbol_section_entity_size = elf_section_get_entity_size(&elf, symbol_section);
	if (!symbol_section_size || !symbol_section_entity_size)
		return ("0 symbol");

	t_elf_word symbol_count = symbol_section_size / symbol_section_entity_size;

	t_elf_symbol *elf_symbol = elf_symbol_from(&elf, symbol_section);
	if (!elf_symbol)
		return ("invalid symbol offset");

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
	if (sort != SORT_NONE)
		list_sort(&list, (t_list_node_compare)&symbol_compare, sort == SORT_REVERSE);

	if (elf.x32)
		list_for_each(&list, (t_list_node_consumer)&symbol_print_x32);
	else if (elf.x64)
		list_for_each(&list, (t_list_node_consumer)&symbol_print_x64);

	list_delete(&list, &free);

	return (NULL);
}

int
main_file(t_nm *nm, const char *file, bool multiple)
{
	struct stat statbuf;

	int fd = open(file, 0);
	if (fd == -1)
	{
		dprintf(STDERR_FILENO, "ft_nm: %s: %s\n", file, strerror(errno));
		return (1);
	}

	int ret = fstat(fd, &statbuf);
	if (ret == -1)
	{
		dprintf(STDERR_FILENO, "ft_nm: %s: %s\n", file, strerror(errno));
		close(fd);
		return (1);
	}

	if (!S_ISREG(statbuf.st_mode))
	{
		dprintf(STDERR_FILENO, "ft_nm: %s: not a regular file\n", file);
		close(fd);
		return (1);
	}

	char *ptr = mmap(NULL, statbuf.st_size, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
	if (!ptr)
	{
		dprintf(STDERR_FILENO, "ft_nm: %s: %s\n", file, strerror(errno));
		close(fd);
		return (1);
	}

	const char *err = main_nm(nm, file, ptr, &statbuf);
	if (err)
		dprintf(STDERR_FILENO, "ft_nm: %s: %s\n", file, err);

	munmap(ptr, statbuf.st_size);
	close(fd);
	return (!!err);
}

int
main(int argc, char **argv)
{
	t_nm nm;
	bzero(&nm, sizeof(nm));

	int file_index = -1;
	if (!flags_parse(&nm.flags, argc, argv, &file_index))
	{
		if (nm.flags.unknown_word)
			dprintf(STDERR_FILENO, "ft_nm: unrecognized option '--%s'\n", nm.flags.unknown_word);
		else
			dprintf(STDERR_FILENO, "ft_nm: invalid option -- '%c'\n", nm.flags.unknown_letter);

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
		int ret = 0;
		for (int index = file_index; index < argc; index++)
			ret |= main_file(&nm, argv[index], argc == 2);
		return (ret);
	}
}
