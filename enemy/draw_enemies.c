#include "../include/cub3d.h"

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

int	draw_enemy(t_map *s, t_character *e)
{
	if (e->visible == false)
		return (0);
	else 
		printf("enemy visible ! \n");
	//draw!!

	return (1);
}