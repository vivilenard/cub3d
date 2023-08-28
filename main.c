
#include "include/cub3d.h"
#include "include/parser.h"

void	full_exit(t_map *s)
{
	//free all
	s = NULL; //dangerous!
	exit(0);
}

void	init_frame(t_map *s, t_frame *frame)
{
	s->frame = frame;
	frame->counter = 0;
}

int	main(int argc, char **argv)
{
	int				fd;
	t_map			s;
	t_map_params	map_params;
	t_frame			frame;

	if (argc < 2)
		return (printf("Error\nexpected a map in format *.cub\n"), EXIT_FAILURE);
	fd = open(argv[1], O_RDONLY);
	if (read(fd, NULL, 0) < 0)
		return (quick_exit("Error\nread() failed\n", fd));
	if (parser(&map_params, &s, argv, fd))
		return (close(fd), EXIT_FAILURE);
	//print_map(&s);
	init_frame(&s, &frame);
	s.mlx = mlx_init(WIDTH, HEIGTH, "cub3d", false);
	if (!s.mlx)
		return (perror("no mlx"), EXIT_FAILURE);
	if (set_textures(&map_params, &s))
		return (EXIT_FAILURE);
	display(&s);
	close(fd);
	mlx_terminate(s.mlx);
	return (EXIT_SUCCESS);
}
