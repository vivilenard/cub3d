
#include "cub3d.h"

void	full_exit()
{
	exit(0);
}

int	main(int argc, char **argv)
{
	t_data	s;

	if (parser(argc, argv))
		return (1);
	s = init(&s, argv);
	s.img = mlx_new_image(s.mlx, WIDTH, HEIGTH);
	if (mlx_image_to_window(s.mlx, s.img, 0, 0) < 0)
		perror("img to w");
	print_coordinates(s);
	draw_minimap(&s);
	raycaster(&s);

	mlx_loop_hook(s.mlx, key_bindings, &s);
	mlx_loop(s.mlx);
	mlx_terminate(s.mlx);
	return (0);
}
