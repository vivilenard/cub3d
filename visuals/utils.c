#include "../include/cub3d.h"

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
