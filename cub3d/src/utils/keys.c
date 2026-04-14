/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: broboeuf <broboeuf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 00:44:57 by broboeuf          #+#    #+#             */
/*   Updated: 2025/07/31 01:26:33 by broboeuf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	key_press(int key, t_game *g)
{
	if (key == FORWARD)
		g->keys.forward = 1;
	else if (key == BACKWARD)
		g->keys.backward = 1;
	else if (key == LEFT)
		g->keys.left = 1;
	else if (key == RIGHT)
		g->keys.right = 1;
	else if (key == LEFT_ARROW)
		g->keys.rot_left = 1;
	else if (key == RIGHT_ARROW)
		g->keys.rot_right = 1;
	else if (key == ESC)
		free_game(g);
	return (0);
}

int	key_release(int key, t_game *g)
{
	if (key == FORWARD)
		g->keys.forward = 0;
	else if (key == BACKWARD)
		g->keys.backward = 0;
	else if (key == LEFT)
		g->keys.left = 0;
	else if (key == RIGHT)
		g->keys.right = 0;
	else if (key == LEFT_ARROW)
		g->keys.rot_left = 0;
	else if (key == RIGHT_ARROW)
		g->keys.rot_right = 0;
	return (0);
}

void	update_player(t_game *g)
{
	if (g->keys.forward)
		move_player_forward(g);
	if (g->keys.backward)
		move_player_backward(g);
	if (g->keys.left)
		move_player_left(g);
	if (g->keys.right)
		move_player_right(g);
	if (g->keys.rot_left)
	{
		g->player.dir -= ROT_SPEED;
		g->player.dir = normalize_angle(g->player.dir);
	}
	if (g->keys.rot_right)
	{
		g->player.dir += ROT_SPEED;
		g->player.dir = normalize_angle(g->player.dir);
	}
}
