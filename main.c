
#include "include/cub3d.h"
#include "include/parser.h"

void	full_exit(t_map *s)
{
	perror("full exit\n");
	int i = 0;
	while (s->tex[i])
	{
		mlx_delete_texture(s->tex[i]);
		i++;
	}
	i = 0;
	// free(s->ray);
	// ft_free2d(s->co);
	//system ("leaks cub3D");
	exit(0);
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

int	main(int argc, char **argv)
{
	int				fd;
	t_map			s;
	t_map_params	map_params;

	if (argc < 2)
		return (printf("Error\nexpected a map in format *.cub\n"), EXIT_FAILURE);
	fd = open(argv[1], O_RDONLY);
	if (read(fd, NULL, 0) < 0)
		return (quick_exit("Error\nread() failed\n", fd));
	s.mlx = mlx_init(WIDTH, HEIGTH, "cub3d", false);
	if (!s.mlx)
		printf("no mlx");
	if (parser(&map_params, &s, argv, fd))
	{
		//free;
		close(fd);
		return (EXIT_FAILURE);
	}
	//print_map(&s);
	//printf("test\n");
	//init(&s);	//need to shift some things to parser
	display(&s);
	return (EXIT_SUCCESS);
}
