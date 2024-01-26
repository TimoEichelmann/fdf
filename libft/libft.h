/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 16:01:44 by teichelm          #+#    #+#             */
/*   Updated: 2024/01/26 19:47:46 by teichelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct stack
{
	int				*value;
	int				*position;
	char			*binary;
	struct stack	*next;
}t_stack;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

t_list			*ft_lstmap(t_list *lst, void *(*f)(void *),
					void (*del)(void *));
void			ft_lstiter(t_list *lst, void (*f)(void *));
void			ft_lstclear(t_list **lst, void (*del)(void*));
void			ft_lstdelone(t_list *lst, void (*del)(void*));
void			ft_lstadd_back(t_list **lst, t_list *new);
t_list			*ft_lstlast(t_list *list);
int				ft_lstsize(t_list *lst);
void			ft_lstadd_front(t_list **lst, t_list *new);
t_list			*ft_lstnew(void *content);
int				ft_atoi(const char *p);
void			ft_bzero(void *str, unsigned int len);
void			*ft_calloc(unsigned int memb, unsigned int size);
int				ft_isalnum(int a);
int				ft_isalpha(int a);
int				ft_isascii(int a);
int				ft_isdigit(int a);
int				ft_isprint(int a);
char			*ft_itoa(int n);
void			*ft_memchr(const void *s, int c, unsigned int n);
int				ft_memcmp(void *str1, void *str2, int len);
void			*ft_memcpy(void *dest, const void *src, unsigned int n);
void			*ft_memmove(void *dest, const void *src, unsigned int n);
void			*ft_memset(void *str, int c, unsigned int len);
void			ft_putchar_fd(char c, int fd);
void			ft_putendl_fd(char *s, int fd);
void			ft_putnbr_fd(int n, int fd);
void			ft_putstr_fd(char *s, int fd);
char			**ft_split(const char *s, char c);
char			*ft_strchr(const char *s, int c);
char			*ft_strdup(const char *s);
void			ft_striteri(char *s, void (*f)(unsigned int, char*));
char			*ft_strjoin(const char *s1, const char *s2);
unsigned int	ft_strlcat(char *dst, const char *src, unsigned int size);
unsigned int	ft_strlcpy(char *dest, char *src, unsigned int size);
int				ft_strlen(const char *a);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int				ft_strncmp(char *s1, char *s2, unsigned int n);
char			*ft_strnstr(const char *big, const char *little,
					unsigned int len);
char			*ft_strtrim(const char *s1, const char *set);
char			*ft_strrchr(const char *s, int c);
char			*ft_substr(const char *s, unsigned int start, unsigned int len);
int				ft_tolower(int c);
int				ft_toupper(int c);
int				ft_printf(const char *p, ...);
int				ft_format(const char *p, va_list args, int i, int result);
int				ft_printchar(char c);
int				ft_printstr(char *p);
int				ft_unsigned_int(unsigned int i);
int				ft_int(int i);
int				ft_void_pointer(void *p);
int				ft_hexconverter_long(unsigned long long int h);
int				ft_hexconverter(unsigned int h, const char *p, int u);
int				ft_hexadecimal_len(unsigned int h);
char			*get_next_line(int fd);
char			*ft_read(int fd, char *stash);
char			*ft_left_stash(char *stash, char *line);
int				ft_nl_check(char *p);
char			*ft_strjoin_gnl(char *stash, char *buf);
char			*ft_getline(char *stash);

#endif
