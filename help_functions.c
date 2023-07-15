/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlenard <vlenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 15:23:10 by vlenard           #+#    #+#             */
/*   Updated: 2023/07/15 13:52:41 by vlenard          ###   ########.fr       */
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
	border = 1;
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
