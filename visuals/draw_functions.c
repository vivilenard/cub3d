#include "../include/cub3d.h"

void	print_square(t_map *s, int x, int y, u_int32_t color)
{
	int	x2;
	int	y2;
	int	border;
	int	radius;

	x2 = 0;
	y2 = 0;
	border = 0;
	radius = s->mm_square;
	while (x2 < radius - border)
	{
		while (y2 < radius - border)
		{
			mlx_put_pixel(s->minimap, x * radius + x2, y * radius + y2, color);
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

void	color_full_screen(mlx_image_t *img, uint32_t color)
{
	uint32_t	x;
	uint32_t	y;

	x = 0;
	y = 0;
	while (x < img->width)
	{
		y = 0;
		while (y < img->height)
		{
			mlx_put_pixel(img, x, y, color);
			y++;
		}
		x++;
	}
}
