#include "../include/cub3d.h"

int	display(t_map *s)
{
	t_ray *ray;

	ray = malloc(sizeof(t_ray));
	s->ray = ray;
	s->img = mlx_new_image(s->mlx, WIDTH, HEIGTH);
	if (!s->img)
		return (1);
	if (mlx_image_to_window(s->mlx, s->img, 0, 0) < 0)
		return (perror("img to window"), 2);
	print_coordinates(*s);
	minimap(s);
	raycaster(s, ray);
	mlx_loop_hook(s->mlx, key_bindings, s);
	mlx_loop(s->mlx);
	return (0);
}
