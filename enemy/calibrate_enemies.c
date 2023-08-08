#include "../include/cub3d.h"

bool	continue_walk(char **co, int x, int y)
{
	if (co[x][y] == WALL || co[x][y] == CLOSED_DOOR)
		return (false);
	return (true);
}

double	angle_vector(double xv, double yv)
{
	double angle;

	angle = acos(sqrtf(xv * xv) / sqrtf(xv * xv + yv * yv));
	if (xv < 0 && yv > 0)
		angle = PI - angle;
	else if (xv < 0 && yv < 0)
		angle = PI + angle;
	else if (xv > 0 && yv < 0)
		angle = 2 * PI - angle;
	return (angle);
}

void	enemy_angles(t_map *s, t_character *e)
{
	e->a = angle_vector(e->x - s->px, e->y - s->py);
	e->a_left = angle_vector(e->left_x - s->px, e->left_y - s->py);
	// e->a_right = e->a - (e->a_left - e->a);
	// if (e->a_right > 2 * PI)
	// 	e->a_right /= 2 * PI;
	e->a_right = angle_vector(e->right_x - s->px, e->right_y - s->py);
	//printf("%d, ea: %f, pa: %f, xdir: %f, ydir: %f\n", e->index, e->a, s->pa, e->x - s->px, e->y - s->py);
	// printf("pa %f\n", s->pa);
	// printf("\t index: %d, ea left: %f, ea: %f, ea right: %f\n", e->index, e->a_left, e->a, e->a_right);
	//printf("index: %d, dist: %f\n", e->index, e->dist);
}

int	calibrate_enemy(t_map *s, t_character *e)
{
	double mv;

	mv = 0.005;
	if (e->dist <= 2)
	{
		if (continue_walk(s->co, (int)(e->x + mv * e->dx), (int)e->y))
			e->x += mv * e->dx;
		if (continue_walk(s->co, (int)e->x, (int)(e->y + mv * e->dy)))
			e->y += mv * e->dy;
	}
	e->dx = s->px - e->x;	//richtungsvektor EP = p - e
	e->dy = s->py - e->y;
	e->dist = sqrt(e->dx * e->dx
		+ e->dy * e->dy);
	enemy_angles(s, e);
	return (1);
}

void	loop_enemies(t_map *s, int (*f)(t_map *s, t_character *e))
{
	int	i;

	i = -1;
	while (s->enemy[++i])
		f(s, s->enemy[i]);
}
