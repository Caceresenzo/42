#include <stdio.h>

const char *program[] = {
	"/*",
	" This program will print its own source when run.",
	" */",
	"",
	"void",
	"print_string(const char *str)",
	"{",
	"	printf(\"	\\\"\");",
	"	while (*str)",
	"	{",
	"		if (*str == '\\\\')",
	"			printf(\"\\\\\\\\\");",
	"		else if (*str == '\"')",
	"			printf(\"\\\\\\\"\");",
	"		else",
	"			printf(\"%c\", *str);",
	"		++str;",
	"	}",
	"	printf(\"\\\",\\n\");",
	"}",
	"",
	"int",
	"main(void)",
	"{",
	"	/*",
	"	 This program will print its own source when run.",
	"	 */",
	"	printf(\"#include <stdio.h>\\n\\n\");",
	"	printf(\"const char *program[] = {\\n\");",
	"	for (const char **line = program; *line; ++line)",
	"		print_string(*line);",
	"	printf(\"	NULL,\\n};\\n\\n\");",
	"	for (const char **line = program; *line; ++line)",
	"		printf(\"%s\\n\", *line);",
	"}",
	NULL,
};

/*
 This program will print its own source when run.
 */

void
print_string(const char *str)
{
	printf("	\"");
	while (*str)
	{
		if (*str == '\\')
			printf("\\\\");
		else if (*str == '"')
			printf("\\\"");
		else
			printf("%c", *str);
		++str;
	}
	printf("\",\n");
}

int
main(void)
{
	/*
	 This program will print its own source when run.
	 */
	printf("#include <stdio.h>\n\n");
	printf("const char *program[] = {\n");
	for (const char **line = program; *line; ++line)
		print_string(*line);
	printf("	NULL,\n};\n\n");
	for (const char **line = program; *line; ++line)
		printf("%s\n", *line);
}
