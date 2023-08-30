
#include "include/display.h"
#include "include/parser.h"

void	free_texture(t_map *map)
{
	mlx_delete_texture(map->tex[NORTH_T]);
	mlx_delete_texture(map->tex[SOUTH_T]);
	mlx_delete_texture(map->tex[EAST_T]);
	mlx_delete_texture(map->tex[WEST_T]);
	mlx_delete_texture(map->tex[DOOR_T]);
	mlx_delete_texture(map->tex[ENEMY_T]);
	mlx_delete_texture(map->tex[HEART_RED_T]);
	mlx_delete_texture(map->tex[HEART_RED_BLACK_T]);
	mlx_delete_texture(map->tex[HEART_BLACK_T]);
}

void	free_map(t_map *map)
{
	int	i;

	i = 0;
	while (i != map->map_height)
	{
		free(map->co[i]);
		i++;
	}
	free(map->co);
	map->co = NULL;
}

void	full_exit(t_map *s)
{
	//free all
	(void)s;
	// s = NULL; //dangerous!
	exit(0);
}

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
	t_map_params	map_params;
	t_frame			frame;

	if (argc < 2)
		return (printf("Error\nexpected a map in format *.cub\n"), EXIT_FAILURE);
	fd = open(argv[1], O_RDONLY);
	if (read(fd, NULL, 0) < 0)
		return (quick_exit("Error\nread() failed\n", fd));
	if (parser(&map_params, &map, argv, fd))
		return (close(fd), EXIT_FAILURE);
	//print_map(&map);
	init_frame(&map, &frame);
	map.mlx = mlx_init(WIDTH, HEIGTH, "cub3d", false);
	if (!map.mlx)
		return (perror("no mlx"), EXIT_FAILURE);
	if (set_textures(&map_params, &map))
		return (EXIT_FAILURE);
	display(&map);
	close(fd);
	mlx_terminate(map.mlx);
	free_map(&map);
	free_texture(&map);
	return (EXIT_SUCCESS);
}
