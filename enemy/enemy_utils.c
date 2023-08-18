#include "../include/cub3d.h"

void	to_vert_line(t_map *s, int p1, int p2, int px, t_character *e)
{
	int	color;
	int	start = p1;
	int	end = p2;

	color = 0xff0000ff;
	if (e->index == 1)
		color = 0xffff00ff;
	if (e->index == 2)
		color = 0xa7c5f9ff;
	if (p2 < p1)
	{
		start = p2;
		end = p1;
	}
	if (start < 0)
		start = 0;
	if (end >= HEIGTH)
		end = HEIGTH - 1;
	while (start < end)
	{
		mlx_put_pixel(s->img, px, start, color);
		start++;
	}
}


void	check_enemy(t_map *s, t_ray *r)
{
	int	i;

	i = -1;
	while (s->enemy[++i])
	{
		if ((r->xmap == (int)s->enemy[i]->x) && r->ymap == (int)s->enemy[i]->y)
			s->enemy[i]->visible = true;
		else if (s->px == (int)s->enemy[i]->x && s->py == (int)s->enemy[i]->y)
			s->enemy[i]->visible = true; //dont need this statement
	}
} 