/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 11:12:23 by ecaceres          #+#    #+#             */
/*   Updated: 2019/08/01 11:12:23 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <fcntl.h>
# include <limits.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define IN 0
# define OUT 1
# define ERR 2

# define BASE_BINARY "01"
# define BASE_OCTAL "01234567"
# define BASE_DECIMAL "0123456789"
# define BASE_HEX_LOW "0123456789abcdef"
# define BASE_HEX_UP "0123456789ABCDEF"

# define FT_STRJOIN_FREE_DONT 0
# define FT_STRJOIN_FREE_FIRST 1
# define FT_STRJOIN_FREE_SECOND 2
# define FT_STRJOIN_FREE_BOTH 3

typedef unsigned char	t_uchar;

typedef struct		s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

long long int		ft_abs(long long int number);
long long int		ft_max(long long int a, long long int b);
long long int		ft_min(long long int a, long long int b);
long long int		ft_zero_if_neg(long long int number);

void				ft_fake_use(void *something);

void				*ft_memset(void *b, int c, size_t len);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
char				*ft_memjoin(void *s1, size_t l1, void *s2, size_t l2);

void				*ft_calloc(size_t count, size_t size);

void				ft_bzero(void *s, size_t n);

char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
char				*ft_strstr(const char *haystack, const char *needle);
char				*ft_strnstr(const char *haystack, const char *needle,
								size_t len);
size_t				ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t				ft_strlcat(char *dst, const char *src, size_t dstsize);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_strcmp(const char *s1, const char *s2);
size_t				ft_strlen(const char *s);
char				*ft_strdup(const char *s1);

char				*ft_emptystr(void);

char				*ft_chrmult(char c, size_t times);
char				*ft_chrtostr(char c);

int					ft_toupper(int c);
int					ft_tolower(int c);

int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_iswspace(int c);
int					ft_islower(int c);
int					ft_isupper(int c);
int					ft_ishex(int c);
int					ft_isoctal(int c);
int					ft_isquote(int c);
int					ft_isinstr(char c, char *charset);

char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strjoin_sided(char const *s1, char const *s2, int side);
char				*ft_strjoin_free(char *s1, char *s2, int flag);
char				*ft_strjoin3(char *s1, char *s2, char *s3);
char				*ft_strtrim(char const *s1, char const *set);
char				**ft_split(char const *s, char c);
size_t				ft_split_length(char **array);
void				*ft_split_free(char ***split_ptr);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int					ft_strcontain(const char *str, char c);
int					ft_str_isdigit(char *str, int allow_signs, int max_sign);

int					ft_atoi(const char *str);

char				*ft_itoa(int n);
size_t				ft_itoa_nsize(long number);
char				*ft_itoa_base(long n, char *base);
size_t				ft_itoa_base_nsize(long number, size_t radix);
char				*ft_itoa_u_base(unsigned long n, char *base);
size_t				ft_itoa_u_base_nsize(unsigned long number, size_t radix);

void				ft_putchar_fd(char c, int fd);
void				ft_putuchar_fd(int c, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);

t_list				*ft_lstnew(void *content);
void				ft_lstadd_front(t_list **alst, t_list *new);
int					ft_lstsize(t_list *lst);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstadd_back(t_list **alst, t_list *new);
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
							void (*del)(void *));

int					ft_lsr(int x, int n);

void				ft_swap_double(double *a, double *b);
void				ft_swap_int(int *a, int *b);

void				ft_sort_comp(int *order, double *dist, int amount);

void				ft_free_and_release(void **ptr_ptr);

int					ft_atoi_base(const char *str, const char *base);
int					ft_atoi_base_insensitive(const char *str, const char *base);

int					ft_is_base_valid(const char *str);
int					ft_base_resolve(const char *base, char match);

#endif
