#include "../include/cub3d.h"

int	print_wall(t_map *s, int x, int y)
{
	if (s->co[y][x] == TERMINAL)
		return (printf("found no coordinate\n"), -1);
	if (s->co[y][x] == WALL || s->co[y][x] == CLOSED_DOOR)
		print_square(s, x, y, 0xFFFFFFFF);
	else
		print_square(s, x, y, 0x303030FF);
	return (0);
}

void	draw_player(t_map	*s)
{
	to_square(s, s->px, s->py, s->p_radius);
}

void	draw_view(t_map *s)
{
	double	vx;
	double	vy;

	vx = s->px + s->pdx / 2;
	vy = s->py + s->pdy / 2;
	if ((vx > 0 && vx < s->map_width)
		&& vy > 0 && vy < s->map_height)
		to_square(s, vx, vy, 0.03);
}

int	draw_mini_enemy(t_map *s, t_character *e)
{
	if (!e->lives)
		return (1);
	if (e->x > 0 && e->y > 0)
		to_red_square(s, e->x, e->y, 0.06);
	return (1);
}

void	minimap_perspective(t_map *s, t_ray *ray)
{
	double	x;
	double	y;
	double	pixel_x;
	double	pixel_y;
	int		pixels;

	x = (ray->hit_x - s->px) * s->mm_square;
	y = (ray->hit_y - s->py) * s->mm_square;
	pixels = (sqrt((x * x) + (y * y)));
	x /= pixels;
	y /= pixels;
	pixel_x = s->px * s->mm_square;
	pixel_y = s->py * s->mm_square;
	while (pixels)
	{
		mlx_put_pixel(s->minimap, (int)(pixel_x), (int)(pixel_y), 0xFF0000FF);
		pixel_x += x;
		pixel_y += y;
		--pixels;
	}
}
