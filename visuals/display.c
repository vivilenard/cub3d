#include "../include/cub3d.h"
//#include "../include/parser.h"

int	display(t_map *s)
{//printf("display\n");
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
{//printf("setup game\n");
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

void	print_cross(t_map *s, float size, int color)
{
	int i;

	i = WIDTH / 2 - size * HEIGTH / 2 - 1;
	while (++i <= WIDTH / 2 + size * HEIGTH / 2)
		mlx_put_pixel(s->img, i, HEIGTH / 2, color);

	i = HEIGTH / 2 - size * HEIGTH / 2 - 1;
	while (++i <= HEIGTH / 2 + size * HEIGTH / 2)
		mlx_put_pixel(s->img, WIDTH / 2, i, color);

}

void	loop_game(void *p)
{//printf("loop game\n");
	t_map *s;

	s = (t_map *) p;
	if (die(s))
		return ;
	check_keys(s);
	loop_enemies(s, calibrate_enemy);
	raycaster(s, s->ray);  //exchanged ray and minimap
	draw_minimap(s);
	print_cross(s, 0.1, 0xFFFFFFAA);
	frame_count(s);
	s->shoot = false;
}