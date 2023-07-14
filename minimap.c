/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karllenard <karllenard@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 10:25:30 by vlenard           #+#    #+#             */
/*   Updated: 2023/07/14 13:54:48 by karllenard       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	print_wall(t_data *s, int x, int y)
{
	if (s->co[x][y] == '1')
		print_square(s->minimap, x, y, s->mm_square, 0xFFFFFFFF);
	return (0);
}

void	draw_player(t_data	*s)
{
	print_square(s->minimap, s->px, s->py, s->mm_square, 0xFF0000FF);
}

int	draw_minimap(t_data *s)
{
	int	radius;

	s->mm_radius = HEIGTH;
	s->minimap = mlx_new_image(s->mlx, s->mm_radius, s->mm_radius);

	radius = s->map_height;
	if (s->map_width > radius)
		radius = s->map_width;

	s->mm_square = s->mm_radius / radius;
	scan_coordinates(s, print_wall);
	draw_player(s);
	if (mlx_image_to_window(s->mlx, s->minimap, 0, 0) < 0)
			full_exit();
	
	return (1);
}