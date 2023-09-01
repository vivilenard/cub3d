/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekulichk <ekulichk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 16:16:18 by ekulichk          #+#    #+#             */
/*   Updated: 2023/09/01 16:55:03 by ekulichk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "../include/parser.h"

int	map_set_init(t_map_set *map_set)
{
	map_set->map_capacity = 1;
	map_set->width_capacity = 1;
	map_set->map = malloc(
			sizeof(t_map_char *) * map_set->map_capacity);
	if (map_set->map == NULL)
		return (print_malloc_failed());
	map_set->all_width = malloc(sizeof(int) * map_set->width_capacity);
	if (map_set->all_width == NULL)
	{
		free(map_set->map);
		return (print_malloc_failed());
	}
	tex_init(map_set);
	map_set->map[0] = NULL;
	map_set->floor.is_color = false;
	map_set->ceiling.is_color = false;
	map_set->max_width = 0;
	map_set->height = 0;
	map_set->player = 0;
	map_set->doors = 0; // ?
	map_set->identifier = 0;
	map_set->map_start = false;
	map_set->map_end = false;
	return (EXIT_SUCCESS);
}

void	tex_init(t_map_set *map_set)
{
	map_set->textures.no = NULL;
	map_set->textures.so = NULL;
	map_set->textures.ea = NULL;
	map_set->textures.we = NULL;
}

double	init_player_view(char c)
{
	if (c == 'N')
		return (PI * 3 / 2);
	if (c == 'E')
		return (2 * PI);
	if (c == 'S')
		return (PI / 2);
	if (c == 'W')
		return (PI);
	return (0);
}
