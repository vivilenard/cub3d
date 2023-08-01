#include "../include/cub3d.h"

void	adjust_view(t_map *s, int x, double mv)
{
	if ( x < WIDTH / 2)
	{
		s->pa -= mv;
		if (s->pa < 0)
			s->pa += 2 * PI;
		s->pdx = cos(s->pa);
		s->pdy = sin(s->pa);
	}
	else if ( x > WIDTH / 2)
	{
		s->pa += mv;
		if (s->pa > 2 * PI)
			s->pa -= 2 * PI;
		s->pdx = cos(s->pa);
		s->pdy = sin(s->pa);
	}
}

void	change_direction_mouse(t_map *s, double mv)
{
	int	x;
	int	y;

	x = 0;
	y = 0;

	mlx_get_mouse_pos(s->mlx, &x, &y);
	adjust_view(s, x, mv);
	mlx_set_mouse_pos(s->mlx, WIDTH / 2, HEIGTH / 2);
}