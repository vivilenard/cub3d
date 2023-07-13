/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlenard <vlenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 10:25:30 by vlenard           #+#    #+#             */
/*   Updated: 2023/07/13 15:59:02 by vlenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	print_wall(t_data *s, int x, int y)
{
	int	square;
	int	radius;

	radius = s->map_height;
	if (s->map_width > radius)
		radius = s->map_width;

	square = s->mm_radius / radius;
	if (s->co[x][y] == '1')
		print_square(s->minimap, x, y, square);
	return (0);
}

int	draw_minimap(t_data *s)
{
	s->mm_radius = HEIGTH;
	s->minimap = mlx_new_image(s->mlx, s->mm_radius, s->mm_radius);
	
	scan_coordinates(s, print_wall);
	if (mlx_image_to_window(s->mlx, s->minimap, 0, 0) < 0)
			full_exit();
	return (1);
}