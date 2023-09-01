/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identifiers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekulichk <ekulichk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 14:15:13 by ekulichk          #+#    #+#             */
/*   Updated: 2023/09/01 14:45:44 by ekulichk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include "../include/parser.h"
#include "../libft/libft.h"
#include "../MLX42/include/MLX42/MLX42.h"

char	*iden_copy(char *src)
{
	int		len;
	char	*dst;

	len = ft_strlen(src);
	dst = malloc(sizeof(char) * (len + 1));
	ft_memcpy(dst, src, sizeof(char) * len);
	return (dst);
}

int	get_identifier(t_map_set *map_set, char *line)
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
		return (free_split(result, i), printf("Error: wrong identifier\n"), EXIT_FAILURE);
	if (set_identifier(map_set, result))
		return (free_split(result, i), printf("Error: wrong identifier\n"), EXIT_FAILURE);
	map_set->identifier++;
	free_split(result, i); 
	return (EXIT_SUCCESS);
}

int	set_identifier(t_map_set *map_set, char **result)
{
	if (ft_strncmp(result[0], "NO\0", 3) == 0 && map_set->textures.no == NULL)
		map_set->textures.no = iden_copy(result[1]);
	else if (ft_strncmp(result[0], "SO\0", 3) == 0
		&& map_set->textures.so == NULL)
		map_set->textures.so = iden_copy(result[1]);
	else if (ft_strncmp(result[0], "EA\0", 3) == 0
		&& map_set->textures.ea == NULL)
		map_set->textures.ea = iden_copy(result[1]);
	else if (ft_strncmp(result[0], "WE\0", 3) == 0
		&& map_set->textures.we == NULL)
		map_set->textures.we = iden_copy(result[1]);
	else if (ft_strncmp(result[0], "F\0", 2) == 0 && !map_set->floor.is_color)
	{
		if (get_color(map_set, 'F', result[1]))
			return (EXIT_FAILURE);
	}
	else if (ft_strncmp(result[0], "C\0", 2) == 0
		&& !map_set->ceiling.is_color)
	{
		if (get_color(map_set, 'C', result[1]))
			return (EXIT_FAILURE);
	}
	else
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	set_textures(t_map_set *map_set, t_map *map)
{
	int			i;
	const char	*side[4];

	i = 0;
	side[NORTH_T] = "textures/wall_no.png";
	side[SOUTH_T] = "textures/wall_so.png";
	side[EAST_T] = "textures/wall_ea.png";
	side[WEST_T] = "textures/wall_we.png";
	map->tex[NORTH_T] = mlx_load_png(map_set->textures.no);
	map->tex[SOUTH_T] = mlx_load_png(map_set->textures.so);
	map->tex[EAST_T] = mlx_load_png(map_set->textures.ea);
	map->tex[WEST_T] = mlx_load_png(map_set->textures.we);
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
	// if (map->tex[DOOR_T] == NULL
	// 	|| map->tex[ENEMY_T] == NULL)
	// 	return (EXIT_FAILURE);
	map->tex[HEART_RED_T] = mlx_load_png("./textures/heart_red.png");
	map->tex[HEART_RED_BLACK_T] = mlx_load_png("./textures/heart_red_black.png");
	map->tex[HEART_BLACK_T] = mlx_load_png("./textures/heart_black.png");
	map->tex[GUN_T] = mlx_load_png("./textures/gun.png");
	free_sides(map_set);
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

void	free_map_set(t_map_set *map_set)
{
	int	i;

	i = 0;
	while (i != map_set->height + 1)
	{
		free(map_set->map[i]);
		i++;
	}
	free(map_set->map);
	free(map_set->all_width);
}

void	free_sides(t_map_set *map_set)
{
	if (map_set->textures.no != NULL)
		free(map_set->textures.no);
	if (map_set->textures.so != NULL)
		free(map_set->textures.so);
	if (map_set->textures.we != NULL)
		free(map_set->textures.we);
	if (map_set->textures.ea != NULL)
		free(map_set->textures.ea);
}
