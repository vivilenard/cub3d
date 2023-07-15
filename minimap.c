/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlenard <vlenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 10:25:30 by vlenard           #+#    #+#             */
/*   Updated: 2023/07/15 13:50:11 by vlenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	print_wall(t_data *s, int x, int y)
{
	if (s->co[x][y] == '1')
		print_square(s->minimap, x, y, s->mm_square, 0xFFFFFFFF);
	else if (s->co[x][y])
		print_square(s->minimap, x, y, s->mm_square, 0x303030FF);
	return (0);
}

void	mm_put_player(t_data *s, double p_radius)
{
	int		a;
	int		b;

	a = (s->px - p_radius) * s->mm_square;
	b = (s->py + p_radius) * s->mm_square;

	while (a < (s->px + p_radius) * s->mm_square)
	{
		while (b > (s->py - p_radius) * s->mm_square)
		{
			mlx_put_pixel(s->minimap, a, b, 0xFF0000FF);
			b--;
		}
		b = (s->py + p_radius) * s->mm_square;
		a++;
	}	
}

void	draw_player(t_data	*s)
{
	//print_square(s->minimap, s->px, s->py, s->mm_square, 0xFF0000FF);
	printf("player pos: %f/%f\n", s->px, s->py);
	mm_put_player(s, s->p_radius);
	//mlx_put_pixel(s->minimap, s->px, s->py, 0xFF0000FF);
}

void	calculate_proportions(t_data *s)
{
	int	map_radius;

	s->mm_radius = HEIGTH;

	map_radius = s->map_height;
	if (s->map_width > map_radius)
		map_radius = s->map_width;

	s->mm_square = s->mm_radius / map_radius;
}

int	draw_minimap(t_data *s)
{
	calculate_proportions(s);
	s->minimap = mlx_new_image(s->mlx, s->mm_radius, s->mm_radius);
	scan_coordinates(s, print_wall);
	draw_player(s);
	if (mlx_image_to_window(s->mlx, s->minimap, 0, 0) < 0)
			full_exit();
	return (1);
}