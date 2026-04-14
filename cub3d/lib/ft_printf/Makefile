# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: broboeuf <broboeuf@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/01 09:16:23 by broboeuf          #+#    #+#              #
#    Updated: 2024/12/02 09:52:42 by broboeuf         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =	ft_printf.c \
		ft_putchar.c \
		ft_puthex_lower.c \
		ft_puthex_upper.c \
		ft_putnbr.c \
		ft_putpointer.c \
		ft_putstr.c \
		ft_set_type.c \

NAME = libftprintf.a
CFLAGS = -Wall -Werror -Wextra 
OBJS = ${SRCS:.c=.o}
LIBC = ar rcs
CC = cc

RM = rm -f

.c.o:
		${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}: ${OBJS}
		${LIBC} ${NAME} ${OBJS}

all: 	${NAME}

clean:
		${RM} ${OBJS}

fclean: clean
		${RM} ${NAME}

re: fclean all

.PHONY : all clean fclean re