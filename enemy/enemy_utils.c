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

void	shoot_enemy(t_map *s, t_character *e)
{
	float	shift_x;
	float	shift_y;

	if (e->lives <= 0)
		return ;
	e->lives--;
	shift_x = e->x - e->dx / sqrtf((e->dx * e->dx + e->dy * e->dy)) * 0.2;
	shift_y = e->y - e->dy / sqrtf((e->dx * e->dx + e->dy * e->dy)) * 0.2;
	if (s->co[(int)shift_y][(int)shift_x] != WALL
		&& s->co[(int)shift_y][(int)shift_x] != CLOSED_DOOR)
	{
		e->x = shift_x;
		e->y = shift_y;
	}
}