/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bressenham.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: broboeuf <broboeuf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 20:43:05 by broboeuf          #+#    #+#             */
/*   Updated: 2025/07/20 20:26:52 by broboeuf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

/**
 * Rend la valeur absolue de *d et ajuste le signe de l'incrément *i
 * @param d pointeur vers la valeur delta
 * @param i pointeur vers l’incrément
 */
static void	absolute(int *d, int *i)
{
	if (*d < 0)
	{
		*i = -1;
		*d = -(*d);
	}
}

/**
 * Trace une ligne avec pente faible (plus horizontale que verticale)
 * @param img image cible
 * @param p1 point de départ
 * @param p2 point d’arrivée
 * @param col couleur
 */
static void	draw_seg_low(t_image *img, t_point p1, t_point p2, int col)
{
	int	dy;
	int	yi;
	int	derive;
	int	x;
	int	y;

	dy = p2.y - p1.y;
	yi = 1;
	absolute(&dy, &yi);
	derive = (2 * dy) - (p2.x - p1.x);
	x = p1.x;
	y = p1.y;
	while (x < p2.x)
	{
		put_pixel(img, x, y, col);
		if (derive > 0)
		{
			y += yi;
			derive += 2 * (dy - (p2.x - p1.x));
		}
		else
			derive += 2 * dy;
		x++;
	}
}

/**
 * Trace une ligne avec pente forte (plus verticale qu’horizontale)
 * @param img image cible
 * @param p1 point de départ
 * @param p2 point d’arrivée
 * @param col couleur
 */
static void	draw_seg_high(t_image *img, t_point p1, t_point p2, int col)
{
	int	dx;
	int	xi;
	int	derive;
	int	y;
	int	x;

	dx = p2.x - p1.x;
	xi = 1;
	absolute(&dx, &xi);
	derive = (2 * dx) - (p2.y - p1.y);
	y = p1.y;
	x = p1.x;
	while (y < p2.y)
	{
		put_pixel(img, x, y, col);
		if (derive > 0)
		{
			x += xi;
			derive += 2 * (dx - (p2.y - p1.y));
		}
		else
			derive += 2 * dx;
		y++;
	}
}

/**
 * Trace une ligne entre deux points en utilisant l’algorithme de Bresenham
 * @param img image cible
 * @param p1 point de départ
 * @param p2 point d’arrivée
 * @param col couleur de la ligne
 */
void	ft_draw_line(t_image *img, t_point p1, t_point p2, int col)
{
	if (abs(p2.y - p1.y) < abs(p2.x - p1.x))
	{
		if (p1.x > p2.x)
			draw_seg_low(img, p2, p1, col);
		else
			draw_seg_low(img, p1, p2, col);
	}
	else
	{
		if (p1.y > p2.y)
			draw_seg_high(img, p2, p1, col);
		else
			draw_seg_high(img, p1, p2, col);
	}
}
