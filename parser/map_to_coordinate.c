/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_to_coordinate.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlenard <vlenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 13:19:19 by vlenard           #+#    #+#             */
/*   Updated: 2023/07/31 13:51:12 by vlenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	assign_line(char *line, t_data *s, int	y)
{
	int	x;
	x = 0;

	while (line[x] && line[x] != '\n')
	{
		s->co[x][y] = line[x];
		x++;
	}
	return (1);
}

int	allocate_map(t_data *s)
{
	int	x;

	x = 0;
	s->co = malloc((s->map_width + 1) * sizeof(char *));
	if (!s->co)
		return (perror("malloc"), 0);
	s->co[s->map_width] = NULL;
	while (x <= s->map_width)
	{
		s->co[x] = ft_calloc(s->map_height + 1, 1);
		if (!s->co[x])
			return (perror("malloc"), 0);
		x++;
	}
	s->co[x] = NULL;
	return (1);
}


int	map_to_koordinate(t_data *s, char *map)
{
	int		fd;
	char	*line;
	int		line_y;

	//i assume the file only constists of the map
	//i check how big the map is to see how big the coordinate system needs to be:
	s->map_height = mapheight(map);
	s->map_width = mapwidth(map);
	line_y = 0;
	if (access(map, F_OK == -1) || access(map, R_OK == -1))
		full_exit();
	allocate_map(s);	//allocating the coordinate system 
	fd = open(map, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		assign_line(line, s, line_y); 	//here i assign each line horizontally, meaning for each y (= number of line) is assign all x values
		line_y++;
		line = get_next_line(fd);
	}
	return (0);
}