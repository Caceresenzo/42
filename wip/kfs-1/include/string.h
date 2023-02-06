#ifndef STRING_H
# define STRING_H

# include <types.h>

# ifndef countof
#  define countof(arr) (sizeof(arr) / sizeof(arr[0]))
# endif

# ifndef NULL
#  define NULL (0)
# endif

#ifdef __cplusplus
extern "C"
{
#endif

	uint32_t strlen(const char *str);
	char* strcpy(char *dest, const char *src);
	void* memset(void *buf, int c, uint32_t len);
	void* memcpy(void *dst, const void *src, uint32_t n);
	void* memmove(void *dest, const void *src, uint32_t n);
	int strcmp(const char *s1, const char *s2);

#ifdef __cplusplus
}
#endif

#endif
