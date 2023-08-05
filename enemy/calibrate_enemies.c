#include "../include/cub3d.h"

int	calibrate_enemy(t_map *s, t_character *e)
{
	//do i need an angle?
	e->dx = s->px - e->x;	//richtungsvektor EP = p - e
	e->dy = s->py - e->y;
	e->dist = sqrt(e->dx * e->dx
		+ e->dy * e->dy);
	printf("%f/%f, dist %f\n", e->dx, e->dy, e->dist);
	if (e->dist <= 2)
	{
		e->x += 0.005 * e->dx;
		e->y += 0.005 * e->dy;
		printf("move enemy\n");
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
