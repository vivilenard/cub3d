#include "../include/display.h"

void	loop_enemies(t_map *s, int (*f)(t_map *s, t_character *e))
{
	int	i;

	i = -1;
	while (s->enemy[++i])
		f(s, s->enemy[i]);
}

bool	continue_walk(t_map_char **co, int x, int y)
{
	if (co[y][x] == WALL || co[y][x] == CLOSED_DOOR)
		return (false);
	return (true);
}

void	check_enemy(t_map *s, t_ray *r)
{
	int	i;

	i = -1;
	while (s->enemy[++i])
	{
		if ((r->xmap == (int)s->enemy[i]->x) && r->ymap == (int)s->enemy[i]->y)
			s->enemy[i]->visible = true;
	}
}

double	angle_of_vector(double xv, double yv)
{
	double	angle;

	angle = acos(sqrtf(xv * xv) / sqrtf(xv * xv + yv * yv));
	if (xv < 0 && yv > 0)
		angle = PI - angle;
	else if (xv < 0 && yv < 0)
		angle = PI + angle;
	else if (xv > 0 && yv < 0)
		angle = 2 * PI - angle;
	return (angle);
}

int	highest_dist_enemy(t_map *s, double *dist)
{
	int		i;
	double	highest_dist;
	int		index;

	i = -1;
	highest_dist = -1;
	index = -1;
	while (s->enemy[++i])
	{
		if (highest_dist < dist[i])
		{
			highest_dist = dist[i];
			index = i;
		}
	}
	return (index);
}
