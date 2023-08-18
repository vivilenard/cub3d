/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlenard <vlenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 10:25:30 by vlenard           #+#    #+#             */
/*   Updated: 2023/08/18 13:52:24 by vlenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	print_wall(t_map *s, int x, int y)
{
	if (!s->co[x][y])
		return (-1);
	if (s->co[x][y] == WALL || s->co[x][y] == CLOSED_DOOR)
		print_square(s->minimap, x, y, s->mm_square, 0xFFFFFFFF);
	else
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
	//printf("mini %d\n", s->mm_square);
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

int	draw_mini_enemy(t_map *s, t_character *e)
{
	e->orth_x = (-1 * e->dy) / sqrtf(e->dy * e->dy + e->dx * e->dx) / 2;
	e->orth_y =  e->dx / sqrtf(e->dy * e->dy + e->dx * e->dx) / 2;
	e->left_x = e->x + e->orth_x * e->radius;
	e->left_y = e->y + e->orth_y * e->radius;
	e->right_x = e->x - e->orth_x * e->radius;
	e->right_y = e->y - e->orth_y * e->radius;
	to_square(s, e->x, e->y, 0.06);

	//draw enemy plane
	to_square(s, e->right_x, e->right_y, 0.05);
	to_square(s, e->left_x, e->left_y, 0.03);
	return (1);
}

int	draw_minimap(t_map *s)
{
	scan_coordinates(s, print_wall);
	draw_player(s);
	loop_enemies(s, draw_mini_enemy);
	return (1);
}

int	setup_minimap(t_map *s)
{
	calculate_proportions(s);
	s->minimap = mlx_new_image(s->mlx, s->mm_radius, s->mm_radius);
	if (mlx_image_to_window(s->mlx, s->minimap, 0, 0) < 0)
		return (0);
	//draw_minimap(s);
	return (1);
}
