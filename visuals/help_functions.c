#include "../include/cub3d.h"

void	print_square(mlx_image_t *img, int x, int y, int radius, u_int32_t color)
{
	int	x2;
	int	y2;
	int	border;

	x2 = 0;
	y2 = 0;
	border = 0;
	while (x2 < radius - border)
	{
		while (y2 < radius - border)
		{
			mlx_put_pixel(img, x * radius + x2, y * radius + y2, color);
			y2++;
		}
		y2 = 0;
		x2++;
	}
}

void	to_red_square(t_map *s, double x, double y, double p_radius)
{
	int		a;
	int		b;

	a = (x - p_radius) * s->mm_square;
	b = (y + p_radius) * s->mm_square;
	while (a < (int)((x + p_radius) * s->mm_square))
	{
		while (b > (int)((y - p_radius) * s->mm_square))
		{
			mlx_put_pixel(s->minimap, a, b, 0xFF0000FF);
			b--;
		}
		b = (y + p_radius) * s->mm_square;
		a++;
	}	
}

void	to_square(t_map *s, double x, double y, double p_radius)
{
	int		a;
	int		b;

	a = (x - p_radius) * s->mm_square;
	b = (y + p_radius) * s->mm_square;
	while (a < (int)((x + p_radius) * s->mm_square))
	{
		while (b > (int)((y - p_radius) * s->mm_square))
		{
			mlx_put_pixel(s->minimap, a, b, 0xFFFFFFFF);
			b--;
		}
		b = (y + p_radius) * s->mm_square;
		a++;
	}	
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

int		collide(t_map_char **co, int x, int y)
{
	if (co[y][x] == WALL || co[y][x] == CLOSED_DOOR)
		return (1);
	return (0);
}