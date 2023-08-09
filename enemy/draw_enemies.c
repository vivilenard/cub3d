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
	}
} 

int	raycast_enemy(t_map *s, t_character *e)
{
	if (e->visible == false)
		return (0);
	double	ray_a;

	ray_a = s->ray->ra;
	if (((ray_a > e->a_left && !(ray_a > e->a_right))
		|| (!(ray_a < e->a_left) && (ray_a < e->a_right)))
			&& e->in_view == false)
	{
		e->in_view = true;
		e->pix_start = s->ray->x_px;
	}
	else if ((ray_a < e->a_left || ray_a > e->a_right) && e->in_view == true)
	{
		e->in_view = false;
		e->pix_end = s->ray->x_px;
	}
	return (1);
}


int	draw_enemy(t_map *s, t_character *e)
{
	if ((!e->pix_start)) //!pixend
		return (0);
	int px = e->pix_start;
	int	lineheight = HEIGTH / e->dist;
	int p1 = HEIGTH / 2 - lineheight / 2;
	int p2 = HEIGTH / 2 + lineheight / 2;
	while (px && (px < e->pix_end && px < WIDTH))
	{
		to_vert_line(s, p1, p2, px, e);
		px++;
	}
	return (1);
}

void	draw_enemies(t_map *s)
{
	int	i;
	int	e_index;
	int	dist[MAX_ENEMIES];

	e_index = 0;
	i = -1;
	while (s->enemy[++i])
		dist[i] = s->enemy[i]->dist;
	while (1)
	{
		e_index = highest_dist_enemy(s, dist);
		if (e_index < 0)
			break;
		draw_enemy(s, s->enemy[e_index]);
		dist[e_index] = 0;
	}
}
