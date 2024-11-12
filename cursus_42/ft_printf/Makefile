NAME = libftprintf.a

CC = gcc

CFLAGS = -Wall -Wextra -Werror

SRC = ft_print_char.c\
	  ft_print_pointer.c\
	  ft_print_decimal.c\
	  ft_print_str.c\
	  ft_printf.c\
	  ft_conversion.c\
	  ft_print_unsigned.c\
	  ft_print_hex_low.c\
	  ft_print_hex_up.c\


OBJ = $(SRC:.c=.o)

ARFLAGS = rcs

RM = rm -f

all : $(NAME)

$(NAME): $(OBJ)
	$(AR) $(ARFLAGS) $(NAME) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
