#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

#define WRITE(data, len) if (write(fd, data, len) == -1) {perror("write");close(fd);return (EXIT_FAILURE);}
#define WRITE_LINE(str) WRITE(str "\n", strlen(str) + 1)
#define FT(x) int main(void){const char *code = #x;x;}

FT(
	int fd = open("Grace_kid.c", O_CREAT | O_WRONLY, 0666);
	if (fd == -1) {
	perror("open");
	return (EXIT_FAILURE);
	}
	WRITE_LINE("#include <stdio.h>");
	WRITE_LINE("#include <stdlib.h>");
	WRITE_LINE("#include <fcntl.h>");
	WRITE_LINE("#include <string.h>");
	WRITE_LINE("#include <unistd.h>");
	WRITE_LINE("");
	WRITE_LINE("#define WRITE(data, len) if (write(fd, data, len) == -1) {perror(\"write\");close(fd);return (EXIT_FAILURE);}");
	WRITE_LINE("#define WRITE_LINE(str) WRITE(str \"\\n\", strlen(str) + 1)");
	WRITE_LINE("#define FT(x) int main(void){const char *code = #x;x;}");
	WRITE_LINE("");
	WRITE_LINE("FT(");
	WRITE("\t", 1);
	while (*code) {
	WRITE(code, 1);
	if ((*code == ';' || *code == '{' || *code == '}') && *(code + 1) == ' ') {
	WRITE("\n\t", 2);
	++code;
	}
	++code;
	}
	WRITE_LINE("\n\t)");
	close(fd);
	return (EXIT_SUCCESS);
	)
