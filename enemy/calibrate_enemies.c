#include "../include/cub3d.h"

bool	continue_walk(char **co, int x, int y)
{
	if (co[x][y] == WALL || co[x][y] == CLOSED_DOOR)
		return (false);
	return (true);
}

int	calibrate_enemy(t_map *s, t_character *e)
{
	double mv;

	mv = 0.005;
	//do i need an angle?
	e->dx = s->px - e->x;	//richtungsvektor EP = p - e
	e->dy = s->py - e->y;
	e->dist = sqrt(e->dx * e->dx
		+ e->dy * e->dy);
	//printf("%f/%f, dist %f\n", e->dx, e->dy, e->dist);
	if (e->dist <= 2)
	{
		if (continue_walk(s->co, (int)(e->x + mv * e->dx), (int)e->y))
			e->x += mv * e->dx;
		if (continue_walk(s->co, (int)e->x, (int)(e->y + mv * e->dy)))
			e->y += mv * e->dy;
	}
	return (1);
}

void	loop_enemies(t_map *s, int (*f)(t_map *s, t_character *e))
{
	int	i;

	i = -1;
	while (s->enemy[++i])
		f(s, s->enemy[i]);
}
