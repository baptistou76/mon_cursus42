# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: broboeuf <broboeuf@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/07 20:59:52 by broboeuf          #+#    #+#              #
#    Updated: 2025/07/12 01:08:12 by broboeuf         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ==================== LIB/Makefile ====================
NAME	= libcub.a

# Dossiers
FT_PRINTF_DIR	= ft_printf
GNL_DIR			= get_next_line
LIBFT_DIR		= libft

# Fichiers sources
SRCS	=	$(wildcard $(FT_PRINTF_DIR)/*.c) \
			$(wildcard $(GNL_DIR)/*.c) \
			$(wildcard $(LIBFT_DIR)/*.c)

OBJS	= ${SRCS:.c=.o}

# Compilation
CC		= cc
CFLAGS	= -Wall -Wextra -Werror
AR		= ar rcs
RM		= rm -f

.c.o:
	${CC} ${CFLAGS} -c $< -o $@

$(NAME): ${OBJS}
	${AR} ${NAME} ${OBJS}

all: $(NAME)

clean:
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re
