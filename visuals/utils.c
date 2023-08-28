#include "../include/cub3d.h"

void	frame_count(t_frame *frames)
{
	if (frames->counter == 4294967295)
		frames->counter = 0;
	frames->counter++;
//	printf("%u\n", frames->counter);
}


int	to_rgbt(int r, int g, int b, int t)
{
	unsigned long int	color;

	color = (r << 24) + (g << 16) + (b << 8) + t;
	return (color);
}

int	scan_coordinates(t_map *s, int (*f)(t_map *s, int x, int y))
{
	int	x;
	int	y;
	
	x = 0;
	y = 0;
	while (y != s->map_height)
	{
		x = 0;
		while (x != s->map_width)
		{
			if (f(s, x, y))
				return (1);
			x++;
		}
		y++;
	}
	return (0);
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

void	print_map(t_map *map)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y != map->map_height)
	{
		x = 0;
		printf("[");
		while (x != map->map_width)
		{
			if (map->co[y][x] == PLAYER)
				printf("\033[1;31mP\033[0;0m");
			else if (map->co[y][x] == ENEMY)
				printf("\033[1;35mX\033[0;0m");
			else if (map->co[y][x] == CLOSED_DOOR)
				printf("\033[1;36mH\033[0;0m");
			// else if (map->map[y][x] == 0)
			// 	printf("X");
			else
				printf("%d", map->co[y][x]);
			x++;
		}
		printf("]\n");
		y++;
	}
	printf("height: %d, width: %d\n", map->map_height, map->map_width);
	printf("player pos: y %f, x %f\n", map->py, map->px);
	printf("player angle: %f\n", map->pa);
	printf("player direction vector: pdx %f, pdy %f\n", map->pdx, map->pdy);
	printf("p_radius %f\n", map->p_radius);
}