/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlenard <vlenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 17:53:23 by vlenard           #+#    #+#             */
/*   Updated: 2023/07/13 10:57:05 by vlenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	set_player(t_data *s, int x, int y)
{
	printf("%d/%d\n", x, y);
	s->px = (double)x;
	s->py = (double)y;
	return (1);
}

int	player_position(t_data *s)
{
	int	x;
	int	y;
	
	x = 0;
	y = 0;
	while (s->co[x])
	{
		while (s->co[x][y])
		{
			if (ft_isalpha(s->co[x][y]))
				return (set_player(s, x, y), 1);
			y++;
		}
		y = 0;
		x++;
	}
	return (0);
}
t_data	init(t_data *s, char **argv)
{
	s = malloc(sizeof(t_data));
	s->mlx = mlx_init(WIDTH, HEIGTH, "cub3d", false);
	map_to_koordinate(s, argv[1]);
	player_position(s);
	return (*s);
}

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

	s->map_height = mapheight(map);
	s->map_width = mapwidth(map);
	line_y = 0;
	if (access(map, F_OK == -1) || access(map, R_OK == -1))
		full_exit();
	allocate_map(s);
	fd = open(map, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		assign_line(line, s, line_y);
		line_y++;
		line = get_next_line(fd);
	}
	return (0);
}