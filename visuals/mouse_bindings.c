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

void mouse_bindings(mouse_key_t button, action_t action, modifier_key_t mods, void *p)
{
	t_map *s;

	s = (t_map *) p;
	mods = 0;
	if (action == MLX_PRESS && button == MLX_MOUSE_BUTTON_LEFT)
		s->shoot = true;
}

void	check_keys(t_map *s)
{
	move_player_vertical(s, 0.05);
	move_player_horizontal(s, 0.04);
	change_direction_keys(s, 0.02);
	change_direction_mouse(s, 0.02);
}