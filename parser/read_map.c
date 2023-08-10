/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekulichk <ekulichk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 11:52:17 by ekulichk          #+#    #+#             */
/*   Updated: 2023/08/10 23:31:51 by ekulichk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include "../include/parser.h"
#include "../libft/libft.h"
#include "../MLX42/include/MLX42/MLX42.h"

int	zero_extend(t_map_params *map_params)
{
	int			i;
	int			i_hight;
	t_map_char	*new_line;

	i = 0;
	i_hight = 0;
	while (i_hight != map_params->height)
	{
		if (map_params->all_width[i_hight] < map_params->max_width)
		{
			new_line = malloc(sizeof(t_map_char) * map_params->max_width);
			if (new_line == NULL)
			{
				// free
				return (EXIT_FAILURE);
			}
			while (i != map_params->all_width[i_hight])
			{
				new_line[i] = map_params->map[i_hight][i];
				i++;
			}
			while (i != map_params->max_width)
			{
				new_line[i] = SPACE;
				i++;
			}
		}
		map_params->map[i_hight] = new_line;
		free(new_line);
		i_hight++;
	}
	return (EXIT_SUCCESS);
}

int	read_map(t_map *map, t_map_params *map_params, int fd)
{
	char	*line;

	if (map_params_init(map_params) || map_init(map))
		return (EXIT_FAILURE);
	line = get_next_line(fd);
	while (line)
	{
		if (*line == '\n')
		{
			if (!map_params->map_start)
			{
				free(line);
				line = get_next_line(fd);
				continue ;
			}
			else if (map_params->map_start && !map_params->map_end)
			{
				free(line);
				line = get_next_line(fd);
				map_params->map_end = true;
				continue ;
			}
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
				map_params->cur_width = 0;
				map_params->all_width[map_params->height] = 0;
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
	// zero_extend(map_params); // free in failure
	print_map(map_params);
	// if (map_verify(map_params))
	// {
	// 	// free
	// 	return (EXIT_FAILURE);
	// }
	// free line ?
	return (EXIT_SUCCESS);
}

void	print_map(t_map_params *map_params)
{
	int	x;
	int	y;

	x = 0;
	printf("hight: %d, widht: %d\n", map_params->height, map_params->max_width);
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
			if (map_params->map[y][x] == PLAYER)
				printf("\033[1;31mP\033[0;37m");
			else if (map_params->map[y][x] == ENEMY)
				printf("\033[1;35mX\033[0;37m");
			else if (map_params->map[y][x] == CLOSED_DOOR)
				printf("\033[1;36mH\033[0;37m");
			else
				printf("%c", map_params->map[y][x]);
			x++;
		}
		printf("]\n");
		y++;
	}
	printf("player pos: y %d, x %d\n", map_params->player_y, map_params->player_x);
}
