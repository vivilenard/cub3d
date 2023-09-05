/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekulichk <ekulichk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 15:01:43 by vlenard           #+#    #+#             */
/*   Updated: 2023/09/05 14:23:33 by ekulichk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/display.h"
#include "include/parser.h"

void	init_frame(t_map *s, t_frame *frame)
{
	s->frame = frame;
	frame->counter = 0;
	frame->n_backstep = 0;
	frame->e_tex = 0;
}

int	main(int argc, char **argv)
{
	int				fd;
	t_map			map;
	t_map_set		map_set;
	t_frame			frame;

	if (argc != 2)
		return (printf("Error: expected a map in format *.cub\n"), EXIT_FAILURE);
	fd = open(argv[1], O_RDONLY);
	if (read(fd, NULL, 0) < 0)
		return (quick_exit("Error: read() failed\n", fd));
	if (parser(&map_set, &map, argv, fd))
		return (close(fd), EXIT_FAILURE);
	init_frame(&map, &frame);
	map.mlx = mlx_init(WIDTH, HEIGTH, "cub3d", false);
	if (map.mlx == NULL)
		return (perror("no mlx"), free_map(&map), EXIT_FAILURE);
	if (set_textures(&map_set, &map))
		return (full_exit(&map), EXIT_FAILURE);
	display(&map);
	close(fd);
	full_exit(&map);
	return (EXIT_SUCCESS);
}
