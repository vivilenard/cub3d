/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlenard <vlenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 16:16:18 by ekulichk          #+#    #+#             */
/*   Updated: 2023/08/29 15:26:49 by vlenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "../include/parser.h"

int	map_params_init(t_map_params *map_params)
{
	map_params->capacity = 1;
	map_params->width_capacity = 1;
	map_params->map = malloc(
			sizeof(t_map_char *) * map_params->capacity);
	if (map_params->map == NULL)
		return (printf("Error: malloc failed\n"), EXIT_FAILURE);
	map_params->map[0] = NULL;
	map_params->all_width = malloc(sizeof(int) * map_params->width_capacity);
	if (map_params->all_width == NULL)
	{
		free(map_params->map);
		return (printf("Error: malloc failed\n"), EXIT_FAILURE);
	}
	tex_init(map_params);
	map_params->floor.is_color = false;
	map_params->ceiling.is_color = false;
	map_params->max_width = 0;
	map_params->height = 0;
	map_params->player = 0;
	map_params->doors = 0;
	map_params->identifier = 0;
	map_params->map_start = false;
	map_params->map_end = false;
	return (EXIT_SUCCESS);
}

void	tex_init(t_map_params *map_params)
{
	map_params->textures.no = NULL;
	map_params->textures.so = NULL;
	map_params->textures.ea = NULL;
	map_params->textures.we = NULL;
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
