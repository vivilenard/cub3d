#include "../include/cub3d.h"

int	display(t_data *s)
{
	s->img = mlx_new_image(s->mlx, WIDTH, HEIGTH);
	if (!s->img)
		return (1);
	if (mlx_image_to_window(s->mlx, s->img, 0, 0) < 0)
		return (perror("img to w"), 2);
	print_coordinates(*s);
	draw_minimap(s);
	raycaster(s);

	mlx_loop_hook(s->mlx, key_bindings, &s);
	mlx_loop(s->mlx);
	mlx_terminate(s->mlx);
	return (0);
}