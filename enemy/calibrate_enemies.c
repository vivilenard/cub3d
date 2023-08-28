#include "../include/cub3d.h"

bool	continue_walk(t_map_char **co, int x, int y)
{
	if (co[y][x] == WALL || co[y][x] == CLOSED_DOOR)
		return (false);
	return (true);
}

void	enemy_angles(t_map *s, t_character *e)
{
	e->a_left = angle_of_vector(e->left_x - s->px, e->left_y - s->py);
	e->a = angle_of_vector(e->x - s->px, e->y - s->py);
	if (e->a < e->a_left)
		e->a = 2 * PI + e->a;
	e->a_right = angle_of_vector(e->right_x - s->px, e->right_y - s->py);
	if (e->a_right < e->a_left)
		e->a_right = e->a + (e->a - e->a_left);
}

void	enemy_borderpoints(t_character *e)
{
	e->orth_x = (-1 * e->dy) / sqrtf(e->dy * e->dy + e->dx * e->dx) / 2;
	e->orth_y =  e->dx / sqrtf(e->dy * e->dy + e->dx * e->dx) / 2;
	e->left_x = e->x + e->orth_x * e->radius;
	e->left_y = e->y + e->orth_y * e->radius;
	e->right_x = e->x - e->orth_x * e->radius;
	e->right_y = e->y - e->orth_y * e->radius;
}

int	calibrate_enemy(t_map *s, t_character *e)
{
	double mv;

	if (!e->lives)
		return (1);
	mv = 0.005;
	if (e->dist <= 3 && e->dist > 0.6)
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
	enemy_borderpoints(e);
	enemy_angles(s, e);
	enemy_invisible(e);
	return (1);
}
