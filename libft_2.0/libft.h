/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thobenel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 17:42:50 by thobenel          #+#    #+#             */
/*   Updated: 2024/05/06 15:59:04 by thobenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <fcntl.h>
# include <limits.h>
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# include "../exec/libft/printf/ft_printf.h"

char					*ft_strrchr(const char *s, int c);
char					*ft_strnstr(const char *s1, const char *s2, size_t n);
size_t					ft_strlen_v2(const char *str);
size_t					ft_strlcpy(char *dst, const char *src, size_t dst_size);
size_t					ft_strlcat(char *dst, const char *src, size_t dstsize);
int						ft_strncmp(const char *s1, const char *s2, size_t n);
char					*ft_strdup_v2(const char *src);
char					*ft_strchr(const char *s, int c);
char					*ft_strjoin_v2(char const *s1, char const *s2);
char					*ft_strtrim(char const *s1, char const *set);
void					*ft_memset(void *b, int c, size_t len);
void					*ft_memmove(void *dst, const void *src, size_t len);
void					*ft_memcpy(void *dst, const void *src, size_t n);
int						ft_memcmp(const void *s1, const void *s2, size_t n);
void					*ft_memchr(const void *s, int c, size_t n);
char					*ft_strmapi(char const *s, char (*f)(unsigned int,
								char));
void					ft_striteri(char *s, void (*f)(unsigned int, char *));
int						ft_isprint(int c);
int						ft_isdigit(int c);
int						ft_isascii(int c);
int						ft_isalpha(int c);
int						ft_isalnum(int c);
void					ft_putchar_fd(char c, int fd);
void					ft_putstr_fd(char *s, int fd);
void					ft_putendl_fd(char *s, int fd);
void					ft_putnbr_fd(int n, int fd);
void					ft_bzero(void *s, size_t n);
int						ft_atoi(const char *str);
char					*ft_itoa(int n);
void					*ft_calloc(size_t nmemb, size_t size);
int						ft_toupper(int c);
int						ft_tolower(int c);
char					*ft_substr(char const *s, unsigned int start,
							size_t len);
char					**ft_split(char const *s, char c);
void					*ft_realloc(void *ptr, size_t new);

//		printf
void					ft_putchar_fd_two(char s, int fd, int *count);
void					ft_putstr_fd_two(char *s, int fd, int *count);
void					ft_putnbr_basefd_one(long long n, char *base, int fd,
							int *count);
void					ft_putnbr_basefd_two(unsigned long long n, char *base,
							int fd, int *count);
int						ft_printf(const char *format, ...);

// bonus

typedef struct s_list
{
	void				*content;
	struct s_list		*next;
}						t_list;

int						ft_lstsize(t_list *lst);
t_list					*ft_lstnew(void *content);
void					ft_lstadd_front(t_list **lst, t_list *new);
void					ft_lstadd_back(t_list **lst, t_list *new);
t_list					*ft_lstlast(t_list *lst);
t_list					*ft_lstmap(t_list *lst, void *(*f)(void *),
							void (*del)(void *));
void					ft_lstclear(t_list **lst, void (*del)(void *));
void					ft_lstiter(t_list *lst, void (*f)(void *));
void					ft_lstdelone(t_list *lst, void (*del)(void *));

typedef struct s_gnl_list
{
	char				*buf_str;
	struct s_gnl_list	*next;
}						t_gnl_list;

void					str_cpy(t_gnl_list *list, char *str);
int						found_nwl(t_gnl_list *s_list);
void					list_new(t_gnl_list **list, char *buf);
int						len_to_newline(t_gnl_list *list);
t_gnl_list				*find_last_node(t_gnl_list *list);
void					create_lst(t_gnl_list **list, int fd);
char					*get_line(t_gnl_list *list);
void					point_mort(t_gnl_list **list, t_gnl_list *cl_node,
							char *buf);
void					poff_list(t_gnl_list **list);
char					*get_next_line(int fd);

#endif
