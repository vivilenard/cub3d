/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekulichk <ekulichk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 11:52:17 by ekulichk          #+#    #+#             */
/*   Updated: 2023/08/08 17:10:11 by ekulichk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include "../include/parser.h"
#include "../libft/libft.h"
#include "../MLX42/include/MLX42/MLX42.h"

t_map_component	convert_char(t_map_params *map_params, char c, int width_position)
{
	if (c == '0' || c == ' ')
		return (SPACE);
	else if (c == '1')
		return (WALL);
	else if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		map_params->player += 1;
		map_params->player_x = width_position;
		map_params->player_y = map_params->height;
		return (PLAYER);
	}
	else if (c == 'H')
		return (CLOSED_DOOR);
	// else if (c == 'I')
	// 	return (OPENED_DOOR);
	else if (c == 'X')
		return (ENEMY);
	else
		return (ERROR);
}

void	print_map(t_map_params *map_params)
{
	int	x;
	int	y;

	x = 0;
	printf("all width: ");
	while (x != map_params->height)
	{
		printf("%d, ", map_params->all_width[x]);
		x++;
	}
	printf("\n");
	x = 0;
	y = 0;
	printf("map\n");
	while (y != map_params->height)
	{
		x = 0;
		printf("[");
		while (x != map_params->all_width[y])
		{
			printf("%c", map_params->map[y][x]);
			x++;
		}
		printf("]\n");
		y++;
	}
}

void	map_extend(t_map_params *map_params)
{
	t_map_component	*new_line;
	size_t			new_capacity;

	new_capacity = map_params->capacity * 2;
	new_line = malloc(sizeof(t_map_component *) * new_capacity);
	// if (new_line == NULL)
	// {
		// free_map(map_params);
		// free_visited(map_params);
		// return (printf("Error: malloc() failed\n"), EXIT_FAILURE);
	// }
	ft_memcpy(
		new_line, map_params->map[map_params->height],
		sizeof(t_map_component) * map_params->capacity);
	// free_map(map_params);
	map_params->map[map_params->height] = new_line;
	map_params->capacity = new_capacity;
}

void	map_push(t_map_params *map_params)
{
	// printf("capac %d, count %d\n", map_params->capacity, map_params->count);
	if (map_params->capacity == map_params->count)
		map_extend(map_params);
	// printf("count %zu, comp [%c]\n", map_params->count, map_params->component);
	map_params->map[map_params->height][map_params->count] = map_params->component;
	// printf("%c", map_params->map[map_params->height][map_params->count]);
	map_params->count += 1;
}

int get_map(t_map_params *map_params, char *line)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(line);
	map_params->map[map_params->height] = malloc(sizeof(t_map_component) * len);
	while (line[i] != '\n' && line[i] != '\0')
	{
		map_params->component = convert_char(map_params, line[i], i);
		// printf("comp in get_map [%c]\n", map_params->component);
		if (map_params->component == ERROR)
		{
			// free map_params_init()
			ft_printf("Error: wrong map component\n");
			return (EXIT_FAILURE);
		}
		map_push(map_params);
		map_params->all_width[map_params->height] = i + 1;
		i++;
	}
	return (EXIT_SUCCESS);
}

int	read_map(t_map *map, t_map_params *map_params, int fd)
{
	char	*line;

	if (map_params_init(map_params))
		return (EXIT_FAILURE);
	if (map_init(map))
		return (EXIT_FAILURE);
	line = get_next_line(fd);
	while (line)
	{
		if (map_params->identifier != 6)
		{
			if (*line == '\n')
			{
				line = get_next_line(fd);
				continue;
			}
			if (get_identifier(map, map_params, line))
				return (EXIT_FAILURE);
		}
		else
		{
			if (*line == '\n') // won't work here, should replace at the beginning
				return (printf("Error: empty line in a map content\n"), EXIT_FAILURE);
			map_params->capacity = 1;
			map_params->count = 0;
			map_params->width = 0;
			get_map(map_params, line);
		}
		line = get_next_line(fd);
		if (line && map_params->identifier == 6)
		{
			map_params->height++;
		}
	}
	print_map(map_params);
	// }
	// if (map_verify(map_params))
	// {
	// 	// free
	// 	return (EXIT_FAILURE);
	// }
	// free line ?
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
