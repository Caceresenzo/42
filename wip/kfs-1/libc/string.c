#include <string.h>

uint32_t strlen(const char *str)
{
	const char *start = str;

	while (*str)
		str++;

	return (str - start);
}

char* strcpy(char *dst, const char *src)
{
	if (dst == NULL && src == NULL)
		return (NULL);

	char *start = dst;
	while (*src)
	{
		*dst = *src;
		src++;
		dst++;
	}

	return (start);
}

void* memmove(void *dst, const void *src, uint32_t len)
{
	char step = +1;
	unsigned char *dest = (unsigned char*)dst;
	unsigned char *source = (unsigned char*)src;

	if (dst > src)
	{
		step = -1;
		dest = (unsigned char*)(dst + len - 1);
		source = (unsigned char*)(src + len - 1);
	}

	uint32_t index = 0;
	while (index < len)
	{
		*dest = *source;
		dest += step;
		source += step;
		index++;
	}

	return (dst);
}
