/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlenard <vlenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 18:38:49 by vlenard           #+#    #+#             */
/*   Updated: 2023/08/22 09:59:27 by vlenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	mapheight(char *map)
{
	char	*line;
	int		i;
	int		fd;

	i = 0;
	fd = open(map, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		i++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (i);
}

int	mapwidth(char *map)
{
	char	*line;
	size_t		len;
	int		fd;

	len = 0;
	fd = open(map, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		if (len < ft_strlen(line))
			len = ft_strlen(line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (len - 1);
}

int	scan_coordinates(t_map *s, int (*f)(t_map *s, int x, int y))
{
	int	x;
	int	y;
	
	x = 0;
	y = 0;
	while (y != s->map_height)
	{
		x = 0;
		while (x != s->map_width)
		{
			if (f(s, x, y))
				return (1);
			x++;
		}
		y++;
	}
	return (0);
}

void	print_coordinates(t_map s)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (s.co[x][y])
	{
	//	printf("y: %d\n", y);
		while (s.co[x][y])
		{
			printf("%c ", s.co[x][y]);
			x++;
		}
		x = 0;
		printf("\n");
		y++;
	}
}


void	print_map(t_map *map)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y != map->map_height)
	{
		x = 0;
		printf("[");
		while (x != map->map_width)
		{
			if (map->co[y][x] == PLAYER)
				printf("\033[1;31mP\033[0;0m");
			else if (map->co[y][x] == ENEMY)
				printf("\033[1;35mX\033[0;0m");
			else if (map->co[y][x] == CLOSED_DOOR)
				printf("\033[1;36mH\033[0;0m");
			// else if (map->map[y][x] == 0)
			// 	printf("X");
			else
				printf("%d", map->co[y][x]);
			x++;
		}
		printf("]\n");
		y++;
	}
	printf("height: %d, width: %d\n", map->map_height, map->map_width);
	printf("player pos: y %f, x %f\n", map->py, map->px);
	printf("player angle: %f\n", map->pa);
	printf("player direction vector: pdx %f, pdy %f\n", map->pdx, map->pdy);
	printf("p_radius %f\n", map->p_radius);
}
