/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlenard <vlenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 10:25:30 by vlenard           #+#    #+#             */
/*   Updated: 2023/07/31 17:50:19 by vlenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	print_wall(t_map *s, int x, int y)
{
	if (s->co[x][y] == '1')
		print_square(s->minimap, x, y, s->mm_square, 0xFFFFFFFF);
	else if (s->co[x][y])
		print_square(s->minimap, x, y, s->mm_square, 0x303030FF);
	return (0);
}

void	draw_player(t_map	*s)
{
	to_square(s, s->px, s->py, s->p_radius);
}

void	calculate_proportions(t_map *s)
{
	int	map_radius;

	s->mm_radius = HEIGTH / 3;	

	map_radius = s->map_height;
	if (s->map_width > map_radius)
		map_radius = s->map_width;

	s->mm_square = s->mm_radius / map_radius;
}

void	draw_view(t_map *s)
{
	double	vx;
	double	vy;

	vx = s->px + s->pdx / 2;
	vy = s->py + s->pdy / 2;

	if ((vx > 0 && vx < s->map_width)
		&& vy > 0 && vy < s->map_height)
		to_square(s, vx, vy, 0.03);
}

int	draw_minimap(t_map *s)
{
	// printf("player pos: %f/%f\n", s->px, s->py);
	// printf("player view: %f/%f\n", s->pdx, s->pdy);
	calculate_proportions(s);
	s->minimap = mlx_new_image(s->mlx, s->mm_radius, s->mm_radius);
	if (mlx_image_to_window(s->mlx, s->minimap, 0, 0) < 0)
		full_exit();
	scan_coordinates(s, print_wall);
	draw_player(s);
	draw_view(s);
	return (1);
}