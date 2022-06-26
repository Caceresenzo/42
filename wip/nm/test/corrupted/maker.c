#include <assert.h>
#include <elf.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>

#define FORK(description_) \
	description = description_; \
	pid = fork(); \
	if (pid == -1) \
	{ \
		perror(description_ ": fork"); \
		return (1); \
	} \
	else if (pid) \
	{ \
		printf("[*] (%d) %s \n", pid, description_); \
		if (waitpid(pid, NULL, 0) == -1) \
		{ \
			perror(description_ ": waitpid"); \
			return (1); \
		} \
	} else

#define SAVE() \
	char out_file[1024]; \
	sprintf(out_file, "saved/%s/%s", file, description); \
	\
	int out_fd = open(out_file, O_WRONLY | O_CREAT | O_TRUNC, 0777); \
	if (out_fd == -1) \
	{ \
		perror("open"); \
		return (1); \
	} \
	\
	if (write(out_fd, ptr, statbuf.st_size) == -1) \
	{ \
		perror("write"); \
		return (1); \
	} \
	\
	close(out_fd); \
	\
	return (0);

Elf64_Shdr*
section_header_find(Elf64_Ehdr *header, Elf64_Word type)
{
	Elf64_Half total = header->e_shnum;
	Elf64_Shdr *section = (void*)((char*)header + header->e_shoff);

	while (total--)
	{
		if (section->sh_type == type)
			return (section);

		++section;
	}

	return (NULL);
}

Elf64_Shdr*
section_header_at(Elf64_Ehdr *header, Elf64_Word index)
{
	Elf64_Half total = header->e_shnum;
	if (index >= total)
		return (NULL);

	Elf64_Shdr *section = (void*)((char*)header + header->e_shoff);
	return (&section[index]);
}

int
main(int argc, char **argv)
{
	const char *program = argv[0];

	if (argc != 2)
	{
		printf("usage: %s <file>", program);
		return (1);
	}

	const char *file = argv[1];

	int fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		perror("open");
		return (1);
	}

	char directory_path[1024];
	sprintf(directory_path, "saved");
	mkdir(directory_path, 0777);
	sprintf(directory_path, "saved/%s", file);
	mkdir(directory_path, 0777);

	struct stat statbuf;
	if (fstat(fd, &statbuf) == -1)
	{
		perror("fstat");
		return (1);
	}

	char *ptr = mmap(NULL, statbuf.st_size, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
	if (!ptr)
	{
		perror("mmap");
		return (1);
	}

	assert(statbuf.st_size >= EI_NIDENT);
	assert(memcmp(ptr, ELFMAG, 4) == 0);
	assert(ptr[EI_CLASS] == ELFCLASS64);

	assert(statbuf.st_size >= sizeof(Elf64_Ehdr));
	Elf64_Ehdr *header = (void*)ptr;

	pid_t pid = 0;
	const char *description = NULL;

	FORK("only null after header")
	{
		memset(ptr + sizeof(Elf64_Ehdr), 0, statbuf.st_size - sizeof(Elf64_Ehdr));

		SAVE();
	}

	FORK("section header to 1")
	{
		header->e_shnum = 1;

		SAVE();
	}

	FORK("section offset to 0")
	{
		header->e_shoff = 0;

		SAVE();
	}

	FORK("section offset to the end of file")
	{
		header->e_shoff = statbuf.st_size;

		SAVE();
	}

	FORK("section offset inverted")
	{
		header->e_shoff = ~header->e_shoff;

		SAVE();
	}

	FORK("section offset to -1")
	{
		header->e_shoff = -1;

		SAVE();
	}

	FORK("section offset to += 2")
	{
		header->e_shoff += 2;

		SAVE();
	}

	FORK("truncated x2")
	{
		statbuf.st_size /= 2;

		SAVE();
	}

	FORK("truncated x4")
	{
		statbuf.st_size /= 4;

		SAVE();
	}

	FORK("truncated x8")
	{
		statbuf.st_size /= 8;

		SAVE();
	}

	FORK("truncated x16")
	{
		statbuf.st_size /= 16;

		SAVE();
	}

	FORK("empty")
	{
		statbuf.st_size = 0;

		SAVE();
	}

	FORK("overflowing strtab")
	{
		Elf64_Shdr *symbol_section_header = section_header_find(header, SHT_SYMTAB);
		assert(symbol_section_header != NULL);

		Elf64_Shdr *strtab_section_header = section_header_at(header, symbol_section_header->sh_link);
		assert(strtab_section_header != NULL);
		assert(strtab_section_header->sh_type == SHT_STRTAB);

		char *data = ptr + strtab_section_header->sh_offset;
		memset(data, 'x', strtab_section_header->sh_size);

//		Elf64_Shdr *section_strtab_section_header = section_header_at(header, header->e_shstrndx);
//		assert(section_strtab_section_header != NULL);
//		assert(section_strtab_section_header->sh_type == SHT_STRTAB);
//
//		data = ptr + section_strtab_section_header->sh_offset;
//		memset(data, 'x', section_strtab_section_header->sh_size);
//
//		printf("%p\n%p\n", strtab_section_header->sh_offset, section_strtab_section_header->sh_offset);

		SAVE();
	}

	return (0);
}
