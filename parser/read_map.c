/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekulichk <ekulichk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 11:52:17 by ekulichk          #+#    #+#             */
/*   Updated: 2023/08/06 00:38:00 by ekulichk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include "../include/parser.h"
#include "../libft/libft.h"
#include "../MLX42/include/MLX42/MLX42.h"

int	set_textures(t_map *map, t_map_params *map_params, t_side side, char *path)
{
	const char	*no_path = "textures/wood.png";
	const char	*so_path = "textures/pillar.png";
	const char	*ea_path = "textures/greystone.png";
	const char	*we_path = "textures/mossy.png";

	map_params->identifier++;
	map->tex[side] = mlx_load_png(path);
	if (map->tex[side] == NULL)
	{
		if (side == NORTH)
			map->tex[side] = mlx_load_png(no_path);
		else if (side == SOUTH)
			map->tex[side] = mlx_load_png(so_path);
		else if (side == EAST)
			map->tex[side] = mlx_load_png(ea_path);
		else if (side == WEST)
			map->tex[side] = mlx_load_png(we_path);
		if (map->tex[side] == NULL)
			return (EXIT_FAILURE);
		else
			printf("Default texture is using\n");
	}
	return (EXIT_SUCCESS);
}

int	get_identifier(t_map *map, t_map_params *map_params, char *str)
{
	int			i;
	int			len;
	char		**result;
	char		**colors;

	i = 0;
	len = ft_strlen(str);
	str[len - 1] = '\0';
	result = ft_split(str, ' ');
	while (result[i])
		i++;
	if (i != 2)
	{
		// free map_init(), result
		printf("Error\nwrong identifier 1\n");
		return (EXIT_FAILURE);
	}
	else if (ft_strncmp(result[0], "NO\0", 3) == 0 && map_params->orintation.no == NULL)
		return (set_textures(map, map_params, NORTH, result[1]));
	else if (ft_strncmp(result[0], "SO\0", 3) == 0 && map_params->orintation.so == NULL)
		return (set_textures(map, map_params, SOUTH, result[1]));
	else if (ft_strncmp(result[0], "EA\0", 3) == 0 && map_params->orintation.ea == NULL)
		return (set_textures(map, map_params, EAST, result[1]));
	else if (ft_strncmp(result[0], "WE\0", 3) == 0 && map_params->orintation.we == NULL)
		return (set_textures(map, map_params, WEST, result[1]));
	else if (ft_strncmp(result[0], "F\0", 2) == 0 && !map_params->floor.is_color)
	{
		map_params->floor.is_color = true;
		map_params->identifier++;
		printf("identifier %d\n", map_params->identifier);
	}
	else if (ft_strncmp(result[0], "C\0", 2) == 0 && !map_params->ceiling.is_color)
	{
		map_params->ceiling.is_color = true;
		map_params->identifier++;
		printf("identifier %d\n", map_params->identifier);
	}
	else
	{
		// free map_init(), result, colors
		printf("Error\nwrong identifier 2\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int get_map(t_map_params *map_params, char *str)
{
	return (EXIT_SUCCESS);
}

int	read_map(t_map *map, t_map_params *map_params, int fd)
{
	int		line_y;
	char	*line;

	if (map_init(map_params))
		return (EXIT_FAILURE);
	line_y = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (*line == '\n')
		{
			line = get_next_line(fd);
			continue;
		}
		 if (map_params->identifier != 6)
		{
			if (get_identifier(map, map_params, line))
				return (EXIT_FAILURE);
		}
		else
		{
			get_map(map_params, line);
		}
		line = get_next_line(fd);
	}
	// }
	// if (map_verify(map_params))
	// {
	// 	// free
	// 	return (EXIT_FAILURE);
	// }
	return (EXIT_SUCCESS);
}

// int	map_verify(t_map_params *map_params)
// {
// 	if (map_params->player != 1)
// 	{
// 		// free
// 		return (printf("Error\nhas to be one player\n"), EXIT_FAILURE);
// 	}
// 	return (EXIT_SUCCESS);
// 	// if map is closed
// }
