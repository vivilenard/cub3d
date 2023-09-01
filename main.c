
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

	if (argc < 2)
		return (printf("Error\nexpected a map in format *.cub\n"), EXIT_FAILURE);
	fd = open(argv[1], O_RDONLY);
	if (read(fd, NULL, 0) < 0)
		return (quick_exit("Error\nread() failed\n", fd));
	if (parser(&map_set, &map, argv, fd))
		return (close(fd), EXIT_FAILURE);
	//print_map(&map);
	init_frame(&map, &frame);
	map.mlx = mlx_init(WIDTH, HEIGTH, "cub3d", false);
	if (map.mlx == NULL)
		return (perror("no mlx"), free_map(&map), EXIT_FAILURE);
	display(&map);
	close(fd);
	full_exit(&map);
	return (EXIT_SUCCESS);
}
