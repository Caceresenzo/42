#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char **argv) {
	if (argc != 2)
	{
		printf("usage: %s <file>\n", argv[0]);
		return (1);
	}

	int fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		perror("open");
		return (1);
	}

	char input[255] = { 0 };
	int length = read(fd, &input, sizeof(input));
	if (length == -1)
	{
		perror("read");
		close(fd);
		return (1);
	}

	if (length > 0 && input[length - 1] == '\n')
		--length;

	for (int index = 0; index < length; ++index)
		input[index] -= index;

	write(1, input, length);
	write(1, "\n", 1);

	close(fd);
	return (0);
}
