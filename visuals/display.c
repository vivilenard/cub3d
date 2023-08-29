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

color	tex_color(mlx_texture_t *tex, int x, int y)
{
	int		pos;
	color	color;
	pos = (y * tex->width + x) * tex->bytes_per_pixel;
	color = to_rgbt(tex->pixels[pos + 0], tex->pixels[pos + 1],
		tex->pixels[pos + 2], tex->pixels[pos + 3]);
	return (color);
}

void	put_texture(t_map *s, mlx_texture_t *tex, double x_pos, double y_pos)
{
	double		tex_step_y;
	double		tex_step_x;
	int			tex_radius;
	double		x_count;
	double		y_count;
	color		color;

	tex_radius = 30;
	tex_step_y = 1.0 * tex->height / tex_radius;
	tex_step_x = 1.0 * tex->width / tex_radius;
	x_count = 0;
	y_count = 0;
	//printf ("tex_step %f\n", tex_step_x);
	while (y_count < tex_radius && HEIGTH * y_pos + y_count < HEIGTH)
	{
		x_count = 0;
		while (x_count < tex_radius && WIDTH * x_pos + x_count < WIDTH)
		{
			color = tex_color(tex, (int)(x_count * tex_step_x), (int)(y_count * tex_step_y));
			if (color)
				mlx_put_pixel(s->img, WIDTH * x_pos + x_count,
					HEIGTH * y_pos + y_count, color);
			x_count++;
		}
		y_count++;
	}

}

void	display_lives(t_map *s)
{
	mlx_texture_t		*heart;
	double				x_pos;
	int					i;

	x_pos = 0.97;
	heart = mlx_load_png("./textures/Vivi_heart.png");
	i = 0;
	while (i < s->lives && i < 15)
	{
		put_texture(s, heart, x_pos, 0.01);
		x_pos -= 0.03;
		i++;
	}
}

void	loop_game(void *p)
{//printf("loop game\n");
	t_map *s;

	s = (t_map *) p;
	if (die(s))
		return ;
	check_keys(s);
	loop_enemies(s, calibrate_enemy);
	draw_minimap(s);
	raycaster(s, s->ray);  //exchanged ray and minimap
	print_cross(s, 0.1, 0xFFFFFFAA);
	display_lives(s);
	frame_count(s->frame);
	s->shoot = false;
}