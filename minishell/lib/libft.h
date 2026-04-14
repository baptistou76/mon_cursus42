/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 12:42:01 by bcaumont          #+#    #+#             */
/*   Updated: 2025/06/13 02:50:31 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# ifndef OPEN_MAX
#  define OPEN_MAX 1024
# endif

# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdarg.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
	struct s_list	*previous;
}					t_list;

int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isprint(int c);
int					ft_isascii(int c);
int					ft_toupper(int c);
int					ft_tolower(int c);
int					ft_isspace(char c);
char				**ft_args_split_free(char **split);
int					ft_atoi(const char *nptr);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
int					ft_lstsize(t_list *list);
char				*ft_strjoin_three(char *s1, char *s2, char *s3);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
char				**args_split(char *str);
char				*ft_strnstr(const char *big, const char *little,
						size_t len);
char				*ft_itoa(int n);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char				**ft_split(char const *s, char c);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strtrim(char const *s1, char const *set);
char				*ft_strdup(const char *s);
char				*ft_strjoin_gnl(char *s1, char *s2);
char				*process_buffer(char *buffer, char *str);
void				delete_old_line(char *buffer);
void				ft_strcat(char **dst_ptr, const char *src);
void				*ft_memset(void *s, int c, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				*ft_memmove(void *dest, const void *src, size_t n);
void				*ft_calloc(size_t nmemb, size_t size);
void				ft_bzero(void *s, size_t n);
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
void				ft_putchar_fd(char c, int fd);
void				ft_putnbr_fd(int n, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_lstadd_front(t_list **lst, t_list *new);
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));
size_t				ft_strlcpy(char *dst, const char *src, size_t size);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
size_t				ft_strlen(const char *str);
t_list				*ft_lstnew(void *content);
t_list				*ft_lstfirst(t_list *lst);
t_list				*ft_lstlast(t_list *lst);
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));
int					ft_is_space(char c);
int					is_new_line(char *str);
long				ft_atol(const char *str);
int					ft_strcmp(char *s1, char *s2);
int					ft_arrlen_pnt(void **array);
void				ft_free_multi(int n, ...);
void				ft_arrfree_pnt(void **arr);
void				ft_free_m(int n, ...);
char				*get_next_line(int fd);
char				*process_buffer(char *buffer, char *str);
char				*ft_strnjoin(char const *s1, char const *s2, int i);
char				*ft_strndup(const char *s1, int j);
int					ft_strchr_i(const char *s, int c);
int					ft_print_char(char c);
int					ft_print_str(char *str);
int					ft_print_decimal(int n);
int					ft_print_pointer(void *ptr);
int					ft_printf(const char *format, ...);
int					ft_conversion(char conversion, va_list args);
int					ft_print_hex_up(unsigned int n);
int					ft_print_hex_low(unsigned int n);
int					ft_print_unsigned(unsigned int n);
int					ft_dprintf(int fd, const char *format, ...);
int					ft_conversion_dprintf(char conversion, va_list args);
int					ft_dprint_char(char c);
int					ft_dprint_str(char *s);
int					ft_dprint_decimal(int n);
int					ft_strlen_gnl(char *s);
void				ft_putchar_fd(char c, int fd);
void				ft_putnbr_fd(int n, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_free_split(char **split);
char				**mega_split(const char *str, const char *delimiters);

#endif