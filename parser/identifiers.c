/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identifiers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekulichk <ekulichk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 14:15:13 by ekulichk          #+#    #+#             */
/*   Updated: 2023/08/31 12:53:07 by ekulichk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include "../include/parser.h"
#include "../libft/libft.h"
#include "../MLX42/include/MLX42/MLX42.h"

char *ft_strcpy(char *src)
{
	char *res;
	
}

int	get_identifier(t_map_params *map_params, char *line)
{
	int			i;
	int			len;
	char		**result;

	i = 0;
	len = ft_strlen(line);
	if (len >= 2)
		line[len - 1] = '\0';
	else
		return (printf("Error: wrong identifier\n"), EXIT_FAILURE);
	result = ft_split(line, ' ');
	if (result == NULL)
		return (printf("Error: wrong identifier\n"), EXIT_FAILURE);
	while (result[i])
		i++;
	if (i != 2)
		return (printf("Error: wrong identifier\n"), EXIT_FAILURE);
	if (set_identifier(map_params, result))
		return (printf("Error: wrong identifier\n"), EXIT_FAILURE);
	map_params->identifier++;
	return (EXIT_SUCCESS);
}

int	set_identifier(t_map_params *map_params, char **result)
{
	if (ft_strncmp(result[0], "NO\0", 3) == 0 && map_params->textures.no == NULL)
		map_params->textures.no = result[1];
	else if (ft_strncmp(result[0], "SO\0", 3) == 0
		&& map_params->textures.so == NULL)
		map_params->textures.so = result[1];
	else if (ft_strncmp(result[0], "EA\0", 3) == 0
		&& map_params->textures.ea == NULL)
		map_params->textures.ea = result[1];
	else if (ft_strncmp(result[0], "WE\0", 3) == 0
		&& map_params->textures.we == NULL)
		map_params->textures.we = result[1];
	else if (ft_strncmp(result[0], "F\0", 2) == 0 && !map_params->floor.is_color)
	{
		if (get_color(map_params, 'F', result[1]))
		{

			return (EXIT_FAILURE);
		}
	}
	else if (ft_strncmp(result[0], "C\0", 2) == 0
		&& !map_params->ceiling.is_color)
	{
		if (get_color(map_params, 'C', result[1]))
		{
			return (EXIT_FAILURE);
		}
	}
	else
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	set_textures(t_map_params *map_params, t_map *map)
{
	int			i;
	const char	*side[4];

	i = 0;
	side[NORTH_T] = "textures/wood.png";
	side[SOUTH_T] = "textures/pillar.png";
	side[EAST_T] = "textures/mossy.png";
	side[WEST_T] = "textures/greystone.png";
	map->tex[NORTH_T] = mlx_load_png(map_params->textures.no);
	map->tex[SOUTH_T] = mlx_load_png(map_params->textures.so);
	map->tex[EAST_T] = mlx_load_png(map_params->textures.ea);
	map->tex[WEST_T] = mlx_load_png(map_params->textures.we);
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
	map->tex[DOOR_T] = mlx_load_png("./textures/door_nebula.png");
	map->tex[ENEMY_T] = mlx_load_png("./textures/enemy_769x110.png");
	if (map->tex[DOOR_T] == NULL
		|| map->tex[ENEMY_T] == NULL)
		return (EXIT_FAILURE);
	map->tex[HEART_RED_T] = mlx_load_png("./textures/heart_red.png");
	map->tex[HEART_RED_BLACK_T] = mlx_load_png("./textures/heart_red_black.png");
	map->tex[HEART_BLACK_T] = mlx_load_png("./textures/heart_black.png");
	map->tex[GUN_T] = mlx_load_png("./textures/gun.png");;
	return (EXIT_SUCCESS);
}

void	free_split(char **str, int i)
{
	while (i != 0)
	{
		free(str[i - 1]);
		i--;
	}
	free(str);
}

void	free_map_params(t_map_params *map_params)
{
	int	i;

	i = 0;
	while (i != map_params->height)
	{
		free(map_params->map[i]);
		i++;
	}
	free(map_params->map);
	free(map_params->all_width);
}
