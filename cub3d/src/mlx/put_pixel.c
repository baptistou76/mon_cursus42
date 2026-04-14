/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 20:28:51 by broboeuf          #+#    #+#             */
/*   Updated: 2025/07/19 21:06:03 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

/**
 * Place un pixel dans l’image à la position (x, y)
 * Ne fait rien si la position est hors de l’écran
 * @param img Image cible (buffer MLX)
 * @param x Coordonnée horizontale
 * @param y Coordonnée verticale
 * @param color Couleur du pixel (format MLX)
 */
void	put_pixel(t_image *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}
