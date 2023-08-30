#include "../include/display.h"

int	display(t_map *s)
{
	if (setup_game(s))
		full_exit(s);
	s->shoot = false;
	mlx_key_hook(s->mlx, key_bindings, s);
	mlx_mouse_hook(s->mlx, mouse_bindings, s);
	mlx_loop_hook(s->mlx, loop_game, s);
	mlx_loop(s->mlx);
	return (0);
}

int	setup_game(t_map *s)
{
	s->ray = malloc(sizeof(t_ray));
	s->img = mlx_new_image(s->mlx, WIDTH, HEIGTH);
	if (!s->img)
		return (1);
	if (mlx_image_to_window(s->mlx, s->img, 0, 0) < 0)
		return (2);
	get_enemies(s);
	if (!setup_minimap(s))
		return (3);
	mlx_set_cursor_mode(s->mlx, MLX_MOUSE_HIDDEN);
	return (0);
}

void	loop_game(void *p)
{
	t_map	*s;

	s = (t_map *) p;
	if (die(s))
		return ;
	check_keys(s);
	loop_enemies(s, calibrate_enemy);
	draw_minimap(s);
	raycaster(s, s->ray);
	display_extras(s);
	frame_count(s->frame);
	s->shoot = false;
}
