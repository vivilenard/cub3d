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

int	raycast_enemy(t_map *s, t_character *e)
{
	if (e->visible == false)
		return (0);
	double	ray_a;

	ray_a = s->ray->ra;
	// if (e->a_left > PI && ray_a < PI)
	// 	ray_a += 2 * PI;
	if (ray_a > e->a_left && ray_a < e->a_right && e->in_view == false)
	{
		e->in_view = true;
		e->pix_start = s->ray->x_px;
		//printf("i see, %f\n", e->pix_start);
	}
	// if (e->a_right > PI && s->ray->ra < PI)
	// 	ray_a = s->ray->ra += 2 * PI;
	else if ((ray_a < e->a_left || ray_a > e->a_right) && e->in_view == true)
	{
		e->in_view = false;
		e->pix_end = s->ray->x_px;
	}

	//printf("ra: %f, ea left: %f, ea: %f, ea right: %f\n", ray_a, e->a_left, e->a, e->a_right);
	//printf("pix1: %f, pix2: %f\n", e->pix_start, e->pix_end);

	return (1);
}