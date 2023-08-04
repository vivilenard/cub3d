
#include "include/cub3d.h"

void	full_exit(t_map *s)
{
	int i = 0;
	while (s->tex[i])
	{
		mlx_delete_texture(s->tex[i]);
		i++;
	}
	i = 0;
	free(s->ray);
	ft_free2d(s->co);
	// while (s->co[i])
	// {
	// 	printf("%s\n", s->co[i]);
	// 	free(s->co[i]);
	// 	i++;
	// }
	// free(s->co);

	//system ("leaks cub3D");
	exit(0);
}

int	main(int argc, char **argv)
{
	int				fd;
	t_map			s;
	t_map_params	map_params;

	// if (parser(argc, argv, &map_params, fd))
	// 	return (EXIT_FAILURE);
	//printf("test\n");
	s = init(&s, argv);
	display(&s);

	return (EXIT_SUCCESS);
}
