#include "../include/display.h"

int	collide(t_map_char **co, int x, int y)
{
	if (co[y][x] == WALL || co[y][x] == CLOSED_DOOR)
		return (1);
	return (0);
}

void	frame_count(t_frame *frames)
{
	if (frames->counter == 4294967295)
		frames->counter = 0;
	frames->counter++;
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
