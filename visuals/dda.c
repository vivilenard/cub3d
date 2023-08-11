#include "../include/cub3d.h"

double	delta_dist(double side)
{
	return (fabs(1 / side));
}

void	check_door(t_map *s, t_ray *r, int px)
{
	if (s->co[r->xmap][r->ymap] == CLOSED_DOOR)
	{
		r->door = 1;
		if (px == WIDTH / 2)		//means player looks right at the door --> could possibly open it
		{
			if (r->raylength < 1)
			{
				r->door_x = r->xmap;
				r->door_y = r->ymap;
			}
		}
	}
}

double	dda(t_map *s, t_ray *r, int px)
{
	while (1)
	{
		if (r->sidedist_x < r->sidedist_y)
		{
			check_enemy(s, s->ray);
			r->xmap += r->xmove;
			r->hit_side = 0;
			if (s->co[r->xmap][r->ymap] == WALL || s->co[r->xmap][r->ymap] == CLOSED_DOOR)
				break ;
			r->sidedist_x += r->deltadist_x;
		}
		else
		{
			check_enemy(s, s->ray);
			r->ymap += r->ymove;
			r->hit_side = 1;
			if (s->co[r->xmap][r->ymap] == WALL || s->co[r->xmap][r->ymap] == CLOSED_DOOR)
				break ;
			r->sidedist_y += r->deltadist_y;
		}
	}
	r->hit_x = s->px + r->rdx * ray_dist(s, r);
	r->hit_y = s->py + r->rdy * ray_dist(s, r);
	r->raylength = ray_dist(s, r) * cos(s->pa - r->ra);
	check_door(s, r, px);
	return (0);
}


double	ray_dist(t_map *s, t_ray *r)
{
	if (s->ray->hit_side == 0)  //unuse s struct
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