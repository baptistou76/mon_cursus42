/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 11:59:33 by bcaumont          #+#    #+#             */
/*   Updated: 2025/01/21 16:16:47 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "libft/libft.h"
# include "ft_printf/ft_printf.h"
# include <ctype.h>
# include <limits.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_node
{
	int					value;
	struct s_node		*next;
	struct s_node		*prev;
}						t_node;

typedef struct s_stack
{
	t_node				*top;
	int					size;
}						t_stack;

typedef struct s_stack_node
{
	int					nbr;
	int					index;
	int					push_cost;
	bool				above_median;
	bool				cheapest;
	struct s_stack_node	*target_node;
	struct s_stack_node	*next;
	struct s_stack_node	*prev;
}						t_stack_node;

int						ft_atoi(const char *nptr);
void					sa(t_stack *stack);
void					pb(t_stack *a, t_stack *b);
void					sb(t_stack *stack);
void					ss(t_stack *a, t_stack *b);
void					pa(t_stack *a, t_stack *b);
void					rb(t_stack *stack);
void					ra(t_stack *stack);
void					rr(t_stack *a, t_stack *b);
void					rra(t_stack *stack);
void					rrb(t_stack *stack);
void					rrr(t_stack *a, t_stack *b);
int						ft_is_valid_number(const char *str);
int						parse_args(t_stack *stack, char **argv);
t_node					*create_node(int value);
void					push(t_stack *stack, int value);
int						pop(t_stack *stack);
void					free_stack(t_stack *stack);
char					**ft_spliter(char *str, char separator);
char					*copy_word(char *str, char separator);
int						word_count(char *str);
int						ft_is_space(char c);
long					ft_atol(const char *str);
void					tiny_sort(t_stack_node **a);

#endif
