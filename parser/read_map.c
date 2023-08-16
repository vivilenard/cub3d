/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekulichk <ekulichk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 11:52:17 by ekulichk          #+#    #+#             */
/*   Updated: 2023/08/16 17:42:08 by ekulichk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include "../include/parser.h"
#include "../libft/libft.h"
#include "../MLX42/include/MLX42/MLX42.h"

int	read_map(t_map *map, t_map_params *map_params, int fd)
{
	char	*line;

	if (map_params_init(map_params))
		return (EXIT_FAILURE);
	if (map_init(map))
	{
		free(map_params->map);
		free(map_params->all_width);
		return (EXIT_FAILURE);
	}
	line = get_next_line(fd);
	while (line)
	{
		if (*line == '\n')
		{
			if (!map_params->map_start)
			{
				;
			}
			else if (map_params->map_start && !map_params->map_end)
				map_params->map_end = true;
		}
		else
		{
			if (map_params->identifier != 6)
			{
				if (get_identifier(map, map_params, line))
					return (EXIT_FAILURE);
			}
			else
			{
				if (get_map(map_params, line))
					return (EXIT_FAILURE);
				map_params->map_start = true;
				map_params->height++;
			}
		}
		if (*line != '\n' && map_params->map_end)
		{
			free(line);
			return (printf("Error: empty line in a map content\n"), EXIT_FAILURE);
		}
		free(line);
		line = get_next_line(fd);
	}
	zero_extend(map_params); // free if failure
	// print_map_params(map_params);
	if (map_verify(map_params))
	{
		// free
		return (EXIT_FAILURE);
	}
	// free line ?
	return (EXIT_SUCCESS);
}

int	zero_extend(t_map_params *map_params)
{
	int			i;
	int			i_height;
	t_map_char	*new_line;

	i = 0;
	i_height = 0;
	while (i_height != map_params->height)
	{
		// printf("%d | %d\n", map_params->all_width[i_height], map_params->max_width);
		if (map_params->all_width[i_height] < map_params->max_width)
		{
			new_line = ft_calloc(map_params->max_width, sizeof(t_map_char));
			ft_memcpy(new_line, map_params->map[i_height], map_params->all_width[i_height] * sizeof(t_map_char));
			free(map_params->map[i_height]);
			map_params->map[i_height] = new_line;

			// for(int i = 0; i < map_params->max_width; i++)
			// 	printf("%d", new_line[i]);
			// printf("\n");

		}
		i_height++;
	}
	return (EXIT_SUCCESS);
}

void	print_map_params(t_map_params *map_params)
{
	int	x;
	int	y;

	x = 0;
	printf("height: %d, width: %d\n", map_params->height, map_params->max_width);
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
		while (x != map_params->max_width)
		{
			if (map_params->map[y][x] == PLAYER)
				printf("\033[1;31mP\033[0;0m");
			else if (map_params->map[y][x] == ENEMY)
				printf("\033[1;35mX\033[0;0m");
			else if (map_params->map[y][x] == CLOSED_DOOR)
				printf("\033[1;36mH\033[0;0m");
			// else if (map_params->map[y][x] == 0)
			// 	printf("X");
			else
				printf("%d", map_params->map[y][x]);
			x++;
		}
		printf("]\n");
		y++;
	}
	printf("player pos: y %d, x %d\n", map_params->player_y, map_params->player_x);
}
