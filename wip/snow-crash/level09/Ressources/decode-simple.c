#include <string.h>
#include <unistd.h>

int main()
{
	char input[] = {"hfnos"};
	int length = strlen(input);

	for (int index = 0; index < length; ++index)
		input[index] -= index;

	write(1, input, length);
	// hello
}
