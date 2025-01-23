/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 18:18:57 by bcaumont          #+#    #+#             */
/*   Updated: 2025/01/23 18:24:50 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <limits.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_stack_node
{
	int					value;
	int					current_position;
	int					final_index;
	int					push_price;
	bool				above_median;
	bool				cheapest;
	struct s_stack_node	*target_node;
	struct s_stack_node	*next;
	struct s_stack_node	*prev;
}						t_stack_node;

//*** Autres ***
char					**ft_split(char *str, char separator);

//*** Gestion des erreurs & free ***
void					free_matrix(char **argv);
void					error_free(t_stack_node **a, char **argv,
							bool flag_argc_2);
void					free_stack(t_stack_node **stack);
int						error_repetition(t_stack_node *a, int nbr);
int						error_syntax(char *str_nbr);

//*** Stack creation ***
void					stack_init(t_stack_node **a, char **argv,
							bool flag_argc_2);
void					init_nodes(t_stack_node *a, t_stack_node *b);
void					set_current_position(t_stack_node *stack);
void					set_price(t_stack_node *a, t_stack_node *b);
void					set_cheapest(t_stack_node *b);

//*** linked list utils ***
void					append_node(t_stack_node **stack, int nbr);
t_stack_node			*find_last_node(t_stack_node *head);
t_stack_node			*find_smallest(t_stack_node *stack);
t_stack_node			*find_highest(t_stack_node *stack);
t_stack_node			*return_cheapest(t_stack_node *stack);
bool					stack_sorted(t_stack_node *stack);
int						stack_len(t_stack_node *stack);
void					finish_rotation(t_stack_node **s, t_stack_node *n,
							char c);

//*** Algorithms ***
void					tiny_sort(t_stack_node **a);
void					push_swap(t_stack_node **a, t_stack_node **b);
void					turk_sort(t_stack_node **a, t_stack_node **b);

//*** Commands ***
void					sa(t_stack_node **a, bool checker);
void					sb(t_stack_node **b, bool checker);
void					ss(t_stack_node **a, t_stack_node **b, bool checker);
void					ra(t_stack_node **a, bool checker);
void					rb(t_stack_node **b, bool checker);
void					rr(t_stack_node **a, t_stack_node **b, bool checker);
void					rra(t_stack_node **a, bool checker);
void					rrb(t_stack_node **b, bool checker);
void					rrr(t_stack_node **a, t_stack_node **b, bool checker);
void					pa(t_stack_node **a, t_stack_node **b, bool checker);
void					pb(t_stack_node **b, t_stack_node **a, bool checker);

//*** Utils pour l'algo ***/
void					move_nodes(t_stack_node **a, t_stack_node **b);
void					min_on_top(t_stack_node **a);
void					move_b_to_a(t_stack_node **a, t_stack_node **b);
void					move_a_to_b(t_stack_node **a, t_stack_node **b);
void					rotate_both(t_stack_node **a, t_stack_node **b,
							t_stack_node *cheapest_node);
void					rev_rotate_both(t_stack_node **a, t_stack_node **b,
							t_stack_node *cheapest_node);
void					prep_for_push(t_stack_node **stack,
							t_stack_node *top_node, char stack_name);
void					swap(t_stack_node **head);

#endif
