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

int strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			break;
		s1++;
		s2++;
	}

	return (*(unsigned char*)s1 - *(unsigned char*)s2);
}
;

void* memset(void *buf, int c, uint32_t len)
{
	unsigned char *ptr = buf;
	while (len--)
		*ptr++ = c;
	return (buf);
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
