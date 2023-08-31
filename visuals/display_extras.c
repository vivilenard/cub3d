#include "../include/display.h"

void	display_extras(t_map *s)
{
	print_cross(s, 0.1, 0xFFFFFFAA);
	display_lives(s);
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

void	put_texture_heart(t_map *s, mlx_texture_t *tex, double x_pos, double y_pos)
{
	double		tex_step;
	int			tex_radius;
	double		x_count;
	double		y_count;
	color		color;

	tex_radius = 30;
	tex_step = 1.0 * tex->height / tex_radius;
	x_count = 0;
	y_count = 0;
	while (y_count < tex_radius && HEIGTH * y_pos + y_count < HEIGTH)
	{
		x_count = 0;
		while (x_count < tex_radius && WIDTH * x_pos + x_count < WIDTH)
		{
			color = tex_color(tex, (int)(x_count * tex_step),
					(int)(y_count * tex_step));
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
	double				x_pos;
	int					i;

	x_pos = 0.97;
	i = 0;
	while (i < LIVES && i < 15)
	{
		if (i < s->lives)
			put_texture_heart(s, s->tex[HEART_RED_T], x_pos, 0.01);
		else
			put_texture_heart(s, s->tex[HEART_BLACK_T], x_pos, 0.01);
		x_pos -= 0.03;
		i++;
	}
}

void	print_cross(t_map *s, float size, int color)
{
	int	i;

	i = WIDTH / 2 - size * HEIGTH / 2 - 1;
	while (++i <= WIDTH / 2 + size * HEIGTH / 2)
		mlx_put_pixel(s->img, i, HEIGTH / 2, color);
	i = HEIGTH / 2 - size * HEIGTH / 2 - 1;
	while (++i <= HEIGTH / 2 + size * HEIGTH / 2)
		mlx_put_pixel(s->img, WIDTH / 2, i, color);
}
