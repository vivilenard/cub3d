/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlenard <vlenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 15:23:10 by vlenard           #+#    #+#             */
/*   Updated: 2023/07/13 15:40:50 by vlenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void print_square(mlx_image_t *img, int x, int y, int radius)
{
	int	x2;
	int	y2;

	x2 = 0;
	y2 = 0;
	while (x2 < radius)
	{
		while (y2 < radius)
		{
			mlx_put_pixel(img, x * radius + x2, y * radius + y2, 0xFFFFFFFF);
			y2++;
		}
		y2 = 0;
		x2++;
	}
}
