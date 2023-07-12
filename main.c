/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlenard <vlenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 12:42:59 by vlenard           #+#    #+#             */
/*   Updated: 2023/07/12 16:18:51 by vlenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	full_exit()
{
	exit(0);
}
t_data	init(t_data *s)
{
	s = malloc(sizeof(t_data));
	s->mlx = mlx_init(WIDTH, HEIGTH, "cub3d", false);
	return (*s);
}

int	assign_line(char *line, t_data *s, int	y)
{
	int	x;
	x = 0;

	while (line[x] && line[x] != '\n')
	{
		s->co[x][y] = line[x];
		printf("%c\n", line[x]);
		x++;
	}
	return (1);
}

int	count_lines(char *map)
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
		line = get_next_line(fd);
	}
	printf("MAP_Y: %d\n", i);
	close(fd);
	return (i);
}

int	map_max_width(char *map)
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
		line = get_next_line(fd);
	}
	printf("MAP_X: %zu\n", len);
	close(fd);
	return (len);
}

int	allocate_map(t_data *s, char *map)
{
	int	x;

	x = 0;
	s->map_height = count_lines(map);
	s->co = malloc((s->map_height + 1) * sizeof(char *));
	if (!s->co)
		return (perror("malloc"), 0);
	s->co[s->map_height] = NULL;
	s->map_width = map_max_width(map);
	while (x < s->map_height + 1)
	{
		s->co[x] = ft_calloc(s->map_width + 1, 1);
		if (!s->co[x])
			return (perror("malloc"), 0);
		x++;
	}
	printf("allocated %d lines\n", x);
	s->co[x] = NULL;
	return (1);
}

int	map_to_koordinate(t_data *s, char *map)
{
	int		fd;
	char	*line;
	int		line_y;

	line_y = 0;
	if (access(map, F_OK == -1) || access(map, R_OK == -1))
		full_exit();
	allocate_map(s, map);
	fd = open(map, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		line_y++;
		printf("%s\n", line);
		assign_line(line, s, line_y);
		line = get_next_line(fd);
	}
	
	return (0);
}

int	parser(t_data *s, int argc, char **argv)
{
	if (argc != 2)
		perror("invalid arguments");
	map_to_koordinate(s, argv[1]);
	return (0);
}

int main(int argc, char **argv)
{
	t_data s;
	s = init(&s);
	parser(&s, argc, argv);
	//raycaster();
	mlx_loop(s.mlx);
	printf("hi\n");
	mlx_terminate(s.mlx);
	return (0);
}