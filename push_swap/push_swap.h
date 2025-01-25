/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 12:28:11 by bcaumont          #+#    #+#             */
/*   Updated: 2025/01/25 15:25:08 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "ft_printf/ft_printf.h"
# include "libft/libft.h"
# include <fcntl.h>
# include <limits.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdlib.h>
# include <string.h>

typedef struct s_node
{
	int				num;
	int				position;
	int				cout;
	bool			above_median;
	bool			cheapest;
	struct s_node	*suivant;
	struct s_node	*precedent;
	struct s_node	*cible;
}					t_node;

/* Definir elements & positions */

void				definir_cible_a(t_node *a, t_node *b);
void				definir_cout_a(t_node *a, t_node *b);
void				definir_cible_b(t_node *a, t_node *b);
void				definir_chaepest(t_node *stack);
void				definir_position(t_node *stack);

/* Trouver les noeuds */
t_node				*plus_gros(t_node *stack);
t_node				*plus_petit(t_node *stack);
t_node				*dernier_noeud(t_node *stack);

/* Verifications */
int					verif_triage(t_node **list);
void				verifs_globales(char *s, t_node *a, long n);
bool				pile_triee(t_node *stack);

/* Liberation de la memoir */
void				free_stack(t_node **stack);
void				free_erreurs(t_node **a);

/* Algorithmes */
void				algo_turc(t_node **a, t_node **b);
void				algo_3(t_node **a);

/* Utils */
int					taille_pile(t_node *stack);
t_node				*return_cheapest(t_node *stack);
int					main(int argc, char **argv);
void				smallest_on_top(t_node **a);
void				prep_for_push(t_node **stack, t_node *top_node,
						char stack_name);

/* Rotations */
void				ra(t_node **stack_a);
void				rb(t_node **stack_b);
void				rr(t_node **stack_a, t_node **stack_b);
void				rotate_both(t_node **a, t_node **b, t_node *cheapest);

/* Rotations inversees */
void				rra(t_node **stack_a);
void				rrb(t_node **stack_b);
void				rrr(t_node **stack_a, t_node **stack_b);
void				rev_rotate_both(t_node **a, t_node **b, t_node *cheapest);

/* Swaps */
void				sa(t_node **stack_a);
void				sb(t_node **stack_b);
void				ss(t_node **stack_a, t_node **stack_b);

/* Poussees */
void				pa(t_node **stack_a, t_node **stack_b);
void				pb(t_node **stack_a, t_node **stack_b);

/* Double liste chainee */
t_node				*add_to_empty(int number);
t_node				*add_at_start(t_node *head, int number);
t_node				*add_at_end(t_node *head, int number);
void				init_dll(int argc, char **argv, t_node **head, int start);

#endif