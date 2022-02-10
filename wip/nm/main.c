#include <assert.h>
#include <unistd.h>
#include <elf.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <sys/fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/unistd.h>

//#define SHT_NULL	  0
//#define SHT_PROGBITS	  1
//#define SHT_SYMTAB	  2
//#define SHT_STRTAB	  3
//#define SHT_RELA	  4
//#define SHT_HASH	  5
//#define SHT_DYNAMIC	  6
//#define SHT_NOTE	  7
//#define SHT_NOBITS	  8
//#define SHT_REL		  9
//#define SHT_SHLIB	  10
//#define SHT_DYNSYM	  11
//#define SHT_INIT_ARRAY	  14
//#define SHT_FINI_ARRAY	  15
//#define SHT_PREINIT_ARRAY 16
//#define SHT_GROUP	  17
//#define SHT_SYMTAB_SHNDX  18
//#define	SHT_NUM		  19

char const *section_header_names[] = { //
[SHT_NULL] = "SHT_NULL", //
[SHT_PROGBITS] = "SHT_PROGBITS", //
[SHT_SYMTAB] = "SHT_SYMTAB", //
[SHT_STRTAB] = "SHT_STRTAB", //
[SHT_RELA] = "SHT_RELA", //
[SHT_HASH] = "SHT_HASH", //
[SHT_DYNAMIC] = "SHT_DYNAMIC", //
[SHT_NOTE] = "SHT_NOTE", //
[SHT_NOBITS] = "SHT_NOBITS", //
[SHT_REL] = "SHT_REL", //
[SHT_SHLIB] = "SHT_SHLIB", //
[SHT_DYNSYM] = "SHT_DYNSYM", //
[SHT_INIT_ARRAY] = "SHT_INIT_ARRAY", //
[SHT_FINI_ARRAY] = "SHT_FINI_ARRAY", //
[SHT_GROUP] = "SHT_GROUP", //
[SHT_SYMTAB_SHNDX] = "SHT_SYMTAB_SHNDX", //
[SHT_NUM] = "SHT_NUM", //
};

unsigned int
reverse(register unsigned int x)
{
	x = (((x & 0xaaaaaaaa) >> 1) | ((x & 0x55555555) << 1));
	x = (((x & 0xcccccccc) >> 2) | ((x & 0x33333333) << 2));
	x = (((x & 0xf0f0f0f0) >> 4) | ((x & 0x0f0f0f0f) << 4));
	x = (((x & 0xff00ff00) >> 8) | ((x & 0x00ff00ff) << 8));
	return ((x >> 16) | (x << 16));

}

int
main(int argc, char **argv)
{
	struct stat statbuf;

	int fd = open("a.out", 0);
	fstat(fd, &statbuf);

	char *ptr = mmap(NULL, statbuf.st_size, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);

	assert(statbuf.st_size > 4);
	assert(memcmp(ptr, ELFMAG, 4) == 0);

	bool is32 = ptr[EI_CLASS] == ELFCLASS32;
	bool is64 = ptr[EI_CLASS] == ELFCLASS64;
	bool isLsb = ptr[EI_DATA] == ELFDATA2LSB;
	bool isMsb = ptr[EI_DATA] == ELFDATA2MSB;

	assert(is32 ^ is64);
	assert(isLsb ^ isMsb);

	printf("x=%d endian=%s\n", is32 ? 32 : 64, isLsb ? "lsb" : "msb");

	Elf64_Ehdr *header = (void*)ptr;
	Elf64_Shdr *section_headers = (void*)(ptr + header->e_shoff);

	Elf64_Shdr *symtab, *dynsym;

	for (int i = 0; i < header->e_shnum; i++)
	{
		Elf64_Shdr *section_header = &section_headers[i];

		{
			Elf64_Shdr *sections = (void*)(ptr + header->e_shoff);
			Elf64_Shdr *shstr = &sections[header->e_shstrndx];
			char *strtab = (void*)(ptr + shstr->sh_offset);

			const char *type = section_header->sh_type <= SHT_LOOS ? section_header_names[section_header->sh_type] : "???";
			const char *name = strtab + section_header->sh_name;

			printf("%2d | %-20s | %-18s | link=%d\n", i, type, name, section_header->sh_link);
		}

		if (section_header->sh_type == SHT_SYMTAB)
			symtab = section_header;
		else if (section_header->sh_type == SHT_DYNSYM)
			dynsym = section_header;
	}

//	{
//		Elf64_Dyn *dyn = (void*)(ptr + dynsym->sh_offset);
//		Elf64_Dyn *dyn_end = (void*)(ptr + dynsym->sh_offset + dynsym->sh_size);
//
//		Elf64_Shdr *sections = (void*)(ptr + header->e_shoff);
//		Elf64_Shdr *shstr = &sections[dynsym->sh_info];
//		char *strtab = (void*)(ptr + shstr->sh_offset);
//
//		while (dyn != dyn_end)
//		{
//			printf("%16p %c %s", dyn, '?', strtab + dyn->d_tag);
//			dyn++;
//		}
//	}

	{
		Elf64_Sym *sym = (void*)(ptr + symtab->sh_offset);
		Elf64_Sym *sym_end = (void*)(ptr + symtab->sh_offset + symtab->sh_size);

		Elf64_Shdr *sections = (void*)(ptr + header->e_shoff);
		Elf64_Shdr *shstr = &sections[symtab->sh_link];
		char *strtab = (void*)(ptr + shstr->sh_offset);

		assert(shstr->sh_type == SHT_STRTAB);

		while (sym != sym_end)
		{
			if (sym->st_name)
				printf("%016lx %c %s\n", (long)sym->st_value, '?', strtab + sym->st_name);
			sym++;
		}
	}
}
