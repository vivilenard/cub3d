/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlenard <vlenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 15:23:10 by vlenard           #+#    #+#             */
/*   Updated: 2023/07/15 16:33:50 by vlenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void print_square(mlx_image_t *img, int x, int y, int radius, u_int32_t color)
{
	int	x2;
	int	y2;
	int border;

	x2 = 0;
	y2 = 0;
	border = 0;
	while (x2 < radius - border)
	{
		while (y2 < radius - border)
		{
			mlx_put_pixel(img, x * radius + x2, y * radius + y2, color);
			y2++;
		}
		y2 = 0;
		x2++;
	}
}

void	to_square(t_data *s, double x, double y, double p_radius)
{
	int		a;
	int		b;

	a = (x - p_radius) * s->mm_square;
	b = (y + p_radius) * s->mm_square;

	while (a < (x + p_radius) * s->mm_square)
	{
		while (b > (y - p_radius) * s->mm_square)
		{
			mlx_put_pixel(s->minimap, a, b, 0xFF0000FF);
			b--;
		}
		b = (y + p_radius) * s->mm_square;
		a++;
	}	
}
