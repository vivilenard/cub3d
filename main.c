/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlenard <vlenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 12:42:59 by vlenard           #+#    #+#             */
/*   Updated: 2023/07/12 18:52:35 by vlenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	full_exit()
{
	exit(0);
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

int	parser(int argc)
{
	if (argc != 2)
		perror("invalid arguments");
	return (0);
}

void	print_coordinates(t_data s)
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

int main(int argc, char **argv)
{
	t_data s;
	s = init(&s, argv);
	parser(argc);
	printf("Height: %d, Width: %d\n", s.map_height, s.map_width);
	print_coordinates(s);
	//raycaster();
	mlx_loop(s.mlx);
	mlx_terminate(s.mlx);
	return (0);
}