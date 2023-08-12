#include "../include/cub3d.h"

void	check_keys(t_map *s)
{
	mlx_set_cursor_mode(s->mlx, MLX_MOUSE_HIDDEN);
	move_player_vertical(s, 0.08);
	move_player_horizontal(s, 0.05);
	change_direction_keys(s, 0.10);
	change_direction_mouse(s, 0.06);
	loop_enemies(s, calibrate_enemy);
}

void	loop_game(void *p)
{
	t_map *s;

	s = (t_map *) p;
	check_keys(s);
	draw_minimap(s);
	raycaster(s, s->ray);
}

int	display(t_map *s)
{
	s->ray = malloc(sizeof(t_ray));
	s->img = mlx_new_image(s->mlx, WIDTH, HEIGTH);
	if (!s->img)
		return (1);
	if (mlx_image_to_window(s->mlx, s->img, 0, 0) < 0)
		return (perror("img to window"), 2);
	mlx_key_hook(s->mlx, key_bindings, s);
	mlx_loop_hook(s->mlx, loop_game, s);
	mlx_loop(s->mlx);
	return (0);
}