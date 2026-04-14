NAME = libft.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
ARFLAGS = rcs
RM = rm -f

SRC = ft_bzero.c \
      ft_atoi.c \
      ft_strappend.c \
      ft_gnl.c \
      ft_isspace.c \
      ft_strjoin_three.c \
      ft_mega_split.c \
      ft_args_split.c \
      ft_args_split_free.c \
      ft_free_split.c \
      ft_isalnum.c \
      ft_isalpha.c \
      ft_isascii.c \
      ft_isdigit.c \
      ft_isprint.c \
      ft_memset.c \
      ft_strlcat.c \
      ft_strlcpy.c \
      ft_strlen.c \
      ft_strncmp.c \
      ft_tolower.c \
      ft_toupper.c \
      ft_memcmp.c \
      ft_memchr.c \
      ft_memcpy.c \
      ft_strnstr.c \
      ft_strchr.c \
      ft_strrchr.c \
      ft_memmove.c \
      ft_calloc.c \
      ft_strjoin.c \
      ft_strmapi.c \
      ft_strdup.c \
      ft_split.c \
      ft_substr.c \
      ft_strtrim.c \
      ft_striteri.c \
      ft_putchar_fd.c \
      ft_putnbr_fd.c \
      ft_putstr_fd.c \
      ft_putendl_fd.c \
      ft_itoa.c \
      ft_is_space.c \
      ft_atol.c \
      ft_strcmp.c \
      ft_arrlen_pnt.c \
      ft_free_multi.c \
      ft_lstnew.c \
      ft_lstadd_front.c \
      ft_lstsize.c \
      ft_lstlast.c \
      ft_lstadd_back.c \
      ft_lstdelone.c \
      ft_lstclear.c \
      ft_lstiter.c \
      ft_lstmap.c \
      ft_arrfree_pnt.c \
      ft_lstfirst.c \
      ft_free_m.c \
      get_next_line.c \
      ft_strnjoin.c \
      ft_strndup.c \
      ft_strchr_i.c \
      ft_print_char.c \
      ft_print_str.c \
      ft_print_decimal.c \
      ft_print_pointer.c \
      ft_printf.c \
      ft_conversion.c \
      ft_print_hex_up.c \
      ft_print_hex_low.c \
      ft_print_unsigned.c \
      ft_dprintf.c \
      ft_conversion_dprintf.c \
      ft_dprint_char.c \
      ft_dprint_str.c \
      ft_dprint_decimal.c \

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@$(AR) $(ARFLAGS) $(NAME) $(OBJ)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJ)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re 