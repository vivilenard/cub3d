#include "../include/cub3d.h"

double	delta_dist(double side)
{
	return (fabs(1 / side));
}

double	dda(t_map *s, t_ray *r)
{
	while (1)
	{
		if (r->sidedist_x < r->sidedist_y)
		{
			r->xmap += r->xmove;
			r->hit_side = 0;
			if (s->co[r->xmap][r->ymap] == '1')
				break ;
			r->sidedist_x += r->deltadist_x;
		}
		else
		{
			r->ymap += r->ymove;
			r->hit_side = 1;
		if (s->co[r->xmap][r->ymap] == '1')
			break ;
			r->sidedist_y += r->deltadist_y;
		}
	}
	r->hit_x = s->px + r->rdx * ray_dist(s, r);
	r->hit_y = s->py + r->rdy * ray_dist(s, r);
	return (0);
}


double	ray_dist(t_map *s, t_ray *r)
{
	if (r->hit_side == 0)
		return (r->sidedist_x);
	return (r->sidedist_y);
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