/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thopgood <thopgood@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 19:24:25 by thopgood          #+#    #+#             */
/*   Updated: 2024/06/30 18:10:13 by thopgood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

// standard libraries
# include <limits.h>
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define GNL_ERROR -1

// list struct
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

// libc
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
size_t				ft_strlen(const char *s);
void				*ft_memset(void *s, int c, size_t n);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				*ft_memmove(void *dest, const void *src, size_t n);
size_t				ft_strlcpy(char *dst, const char *src, size_t size);
size_t				ft_strlcat(char *dst, const char *source, size_t dst_size);
int					ft_toupper(int c);
int					ft_tolower(int c);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
char				*ft_strnstr(const char *big, const char *little,
						size_t len);
int					ft_atoi(const char *nptr);

void				*ft_calloc(size_t nitems, size_t size);
char				*ft_strdup(const char *s);

// additional
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s1, char const *set);
char				**ft_split(char const *s, char c);
char				*ft_itoa(int n);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);

// bonus
t_list				*ft_lstnew(void *content);
void				ft_lstadd_front(t_list **lst, t_list *new);
int					ft_lstsize(t_list *lst);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));

// extra
int					ft_isspace(char c);
void				ft_putbase_fd(int n, const char *base, int fd);
long				ft_abs(long n);
int					get_next_line(int fd, char **line);
char				*ft_strpbrk(const char *s1, const char *s2);
int					count_words(char *str, char *set);
// size_t			ft_numlen(long n);

// ft_printf
# define HEXUPPER_BASE "0123456789ABCDEF"
# define HEXLOWER_BASE "0123456789abcdef"
# define HEX_PREF "0x"
# define NIL_MSG "(nil)"
# define DEC_BASE "0123456789"
# define NULL_MSG "(null)"

int					ft_printdigit(long n, const char *base);
int					ft_printudigit(unsigned long long n, const char *base);
int					ft_printhex(unsigned long long n, char c);
int					ft_printptr(unsigned long long ptr);
int					ft_printdec(long n);
int					ft_printchar(int c);
int					ft_printstr(char *str);
int					ft_printf(const char *format, ...);

#endif