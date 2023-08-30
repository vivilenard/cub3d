#include "../include/cub3d.h"

double	ray_dist(t_ray *r)
{
	if (r->hit_side == XSIDE)
		return (r->sidedist_x);
	return (r->sidedist_y);
}

int	move_side(t_map *s, t_ray *r, int px, int side)
{
	check_enemy(s, s->ray);
	if (side == XSIDE)
	{
		r->xmap += r->xmove;
		r->hit_side = XSIDE;
	}
	else if (side == YSIDE)
	{
		r->ymap += r->ymove;
		r->hit_side = YSIDE;
	}
	check_door(s, r, px);
	if (s->co[r->ymap][r->xmap] == WALL
		|| s->co[r->ymap][r->xmap] == CLOSED_DOOR)
		return (0);
	if (side == XSIDE)
		r->sidedist_x += r->deltadist_x;
	else if (side == YSIDE)
		r->sidedist_y += r->deltadist_y;
	return (1);
}

double	dda(t_map *s, t_ray *r, int px)
{
	init_dda(s, r);
	while (1)
	{
		if (r->sidedist_x < r->sidedist_y)
		{
			if (!move_side(s, r, px, XSIDE))
				break ;
		}
		else if (r->sidedist_y < r->sidedist_x)
		{
			if (!move_side(s, r, px, YSIDE))
				break ;
		}
	}
	r->hit_x = s->px + r->rdx * ray_dist(r);
	r->hit_y = s->py + r->rdy * ray_dist(r);
	return (0);
}

void	init_dda(t_map *s, t_ray *r)
{
	if (r->rdx < 0)
	{
		r->xmove = -1;
		r->sidedist_x = delta_dist(r->rdx) * ((double)(s->px - r->xmap));
	}
	else
	{
		r->xmove = 1;
		r->sidedist_x = delta_dist(r->rdx) * ((double)(r->xmap + 1) - s->px);
	}
	if (r->rdy < 0)
	{
		r->ymove = -1;
		r->sidedist_y = delta_dist(r->rdy) * ((double)(s->py - r->ymap));
	}
	else
	{
		r->ymove = 1;
		r->sidedist_y = delta_dist(r->rdy) * ((double)(r->ymap + 1) - s->py);
	}
}
