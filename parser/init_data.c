/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekulichk <ekulichk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 16:16:18 by ekulichk          #+#    #+#             */
/*   Updated: 2023/09/01 18:30:27 by ekulichk         ###   ########.fr       */
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

int	set_textures(t_map_set *map_set, t_map *map)
{
	int	i;

	i = 4;
	map->tex[NORTH_T] = mlx_load_png(map_set->textures.no);
	map->tex[SOUTH_T] = mlx_load_png(map_set->textures.so);
	map->tex[EAST_T] = mlx_load_png(map_set->textures.ea);
	map->tex[WEST_T] = mlx_load_png(map_set->textures.we);
	if (check_textures(map))
		return (EXIT_FAILURE);
	map->tex[DOOR_T] = mlx_load_png("./textures/door_nebula.png");
	map->tex[ENEMY_T] = mlx_load_png("./textures/enemy_769x110.png");
	map->tex[HEART_RED_T] = mlx_load_png("./textures/heart_red.png");
	map->tex[HEART_BLACK_T] = mlx_load_png("./textures/heart_black.png");
	map->tex[GUN_T] = mlx_load_png("./textures/gun.png");
	while (i != N_TEX)
	{
		if (map->tex[i] == NULL)
			return (EXIT_FAILURE);
		i++;
	}
	free_sides(map_set);
	return (EXIT_SUCCESS);
}

int	check_textures(t_map *map)
{
	int			i;
	const char	*side[4];

	i = 0;
	side[NORTH_T] = "textures/wall_no.png";
	side[SOUTH_T] = "textures/wall_so.png";
	side[EAST_T] = "textures/wall_ea.png";
	side[WEST_T] = "textures/wall_we.png";
	while (i != 4)
	{
		if (map->tex[i] == NULL)
		{
			map->tex[i] = mlx_load_png(side[i]);
			if (map->tex[i] == NULL)
				return (EXIT_FAILURE);
			printf("Default texture is used\n");
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
