/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekulichk <ekulichk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 11:52:17 by ekulichk          #+#    #+#             */
/*   Updated: 2023/09/01 14:45:44 by ekulichk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include "../include/parser.h"
#include "../libft/libft.h"
#include "../MLX42/include/MLX42/MLX42.h"

int	read_map(t_map_set *map_set, int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line != NULL)
	{
		if (*line == '\n')
		{
			if (map_set->map_start && !map_set->map_end)
				map_set->map_end = true;
		}
		else
		{
			if (proceed_line(map_set, line))
				return (free(line), EXIT_FAILURE);
		}
		if (*line != '\n' && map_set->map_end)
			return (free(line), printf("Error: empty line in a map content\n"),
				EXIT_FAILURE);
		free(line);
		line = get_next_line(fd);
	}
	return (EXIT_SUCCESS);
}

int	proceed_line(t_map_set *map_set, char *line)
{
	if (map_set->identifier != 6)
	{
		if (get_identifier(map_set, line))
			return (EXIT_FAILURE);
	}
	else
	{
		if (get_map(map_set, line))
			return (EXIT_FAILURE);
		map_set->map_start = true;
		map_set->height++;
	}
	return (EXIT_SUCCESS);
}

void	print_map_set(t_map_set *map_set)
{
	int	x;
	int	y;

	x = 0;
	printf("height: %d, width: %d\n", map_set->height, map_set->max_width);
	printf("all width: ");
	while (x != map_set->height)
	{
		printf("%d, ", map_set->all_width[x]);
		x++;
	}
	printf("\n");
	x = 0;
	y = 0;
	printf("map\n");
	while (y != map_set->height)
	{
		x = 0;
		printf("[");
		while (x != map_set->max_width)
		{
			if (map_set->map[y][x] == PLAYER)
				printf("\033[1;31mP\033[0;0m");
			else if (map_set->map[y][x] == ENEMY)
				printf("\033[1;35mX\033[0;0m");
			else if (map_set->map[y][x] == CLOSED_DOOR)
				printf("\033[1;36mH\033[0;0m");
			// else if (map_set->map[y][x] == 0)
			// 	printf("X");
			else
				printf("%d", map_set->map[y][x]);
			x++;
		}
		printf("]\n");
		y++;
	}
	printf("player pos: y %d, x %d\n", map_set->player_y, map_set->player_x);
}
