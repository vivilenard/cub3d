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

void	to_square(t_map *s, double x, double y, double p_radius)
{
	int		a;
	int		b;

	//printf("tosq\n");
	a = (x - p_radius) * s->mm_square;
	b = (y + p_radius) * s->mm_square;
	//printf("x %f\n, radius %f\n", x, p_radius);
	//printf("a %d, a2 %d\n", a, (int)(x + p_radius) * s->mm_square);
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

int	to_rgbt(int r, int g, int b, int t)
{
	unsigned long int	color;

	color = (r << 24) + (g << 16) + (b << 8) + t;
	return (color);
}

int		collide(t_map_char **co, int x, int y)
{
	if (co[y][x] == WALL || co[y][x] == CLOSED_DOOR)
		return (1);
	return (0);
}