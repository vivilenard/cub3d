#include "../include/cub3d.h"

void	door_inaccessible(t_ray *ray) //deleted memset
{
	ray->door_x = -1;
	ray->door_y = -1;
}

void	check_door(t_map *s, t_ray *r, int px)
{
	r->raylength = ray_dist(r) * cos(s->pa - r->ra);
	if (s->co[r->ymap][r->xmap] == CLOSED_DOOR
		|| s->co[r->ymap][r->xmap] == OPENED_DOOR)
	{
		if (s->co[r->ymap][r->xmap] == CLOSED_DOOR)
			r->door_visible = 1;
		if (px == WIDTH / 2)
		{
			if (r->raylength < 1)
			{
				r->door_x = r->xmap;
				r->door_y = r->ymap;
			}
		}
	}
}

void	door_mov(t_map *s)
{
	if (s->ray->door_x < 0 && s->ray->door_y < 0)
		return ;
	if (s->co[s->ray->door_y][s->ray->door_x] == CLOSED_DOOR)
		s->co[s->ray->door_y][s->ray->door_x] = OPENED_DOOR;
	else if (s->co[s->ray->door_y][s->ray->door_x] == OPENED_DOOR)
		s->co[s->ray->door_y][s->ray->door_x] = CLOSED_DOOR;
}