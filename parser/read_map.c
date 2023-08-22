/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekulichk <ekulichk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 11:52:17 by ekulichk          #+#    #+#             */
/*   Updated: 2023/08/22 13:48:23 by ekulichk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include "../include/parser.h"
#include "../libft/libft.h"
#include "../MLX42/include/MLX42/MLX42.h"

int	read_map(t_map_params *map_params, int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line != NULL)
	{
		if (*line == '\n')
		{
			if (map_params->map_start && !map_params->map_end)
				map_params->map_end = true;
		}
		else
		{
			if (proceed_line(map_params, line))
				return (EXIT_FAILURE);
		}
		if (*line != '\n' && map_params->map_end)
			return (printf("Error: empty line in a map content\n"),
				EXIT_FAILURE);
		line = get_next_line(fd);
	}
	return (EXIT_SUCCESS);
}

int	proceed_line(t_map_params *map_params, char *line)
{
	if (map_params->identifier != 6)
	{
		if (get_identifier(map_params, line))
		{

			return (EXIT_FAILURE);
		}
	}
	else
	{
		if (get_map(map_params, line))
		{
			return (EXIT_FAILURE);
		}
		map_params->map_start = true;
		map_params->height++;
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
