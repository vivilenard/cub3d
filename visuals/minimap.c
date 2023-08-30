/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlenard <vlenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 10:25:30 by vlenard           #+#    #+#             */
/*   Updated: 2023/08/30 14:36:04 by vlenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	calculate_proportions(t_map *s)
{
	int	map_radius;

	s->mm_radius = HEIGTH / 3;
	map_radius = s->map_height;
	if (s->map_width > map_radius)
		map_radius = s->map_width;
	s->mm_square = s->mm_radius / map_radius;
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
	draw_minimap(s);
	return (1);
}
