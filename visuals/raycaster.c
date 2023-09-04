/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlenard <vlenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 14:42:18 by vlenard           #+#    #+#             */
/*   Updated: 2023/09/04 17:36:52 by vlenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/display.h"

t_ray	*init_ray(t_map *s, t_ray *ray, double angle, int px)
{
	double	pa;

	pa = s->pa;
	ray->x_px = px;
	if ((s->pa - angle * WIDTH / 2 + px * angle) <= 0)
		pa += 2 * PI;
	if ((s->pa - angle * WIDTH / 2 + px * angle) > 2 * PI)
		pa -= 2 * PI;
	ray->ra = pa - angle * WIDTH / 2 + px * angle;
	ray->rdx = cos(ray->ra);
	ray->rdy = sin(ray->ra);
	ray->deltadist_x = delta_dist(ray->rdx);
	ray->deltadist_y = delta_dist(ray->rdy);
	ray->xmap = (int)s->px;
	ray->ymap = (int)s->py;
	ray->hit_side = 0;
	ray->hit_x = 0;
	ray->hit_y = 0;
	ray->lineheight = 0;
	ray->raylength = 0;
	ray->door_visible = 0;
	return (ray);
}

void	draw_stripe(t_map *s, t_ray *r, double dist, int px)
{
	int	drawstart;
	int	drawend;

	r->lineheight = calculate_lineheight(dist);
	drawstart = HEIGTH / 2 - r->lineheight / 2;
	if (drawstart < 0)
		drawstart = 0;
	drawend = HEIGTH / 2 + r->lineheight / 2;
	if (drawend >= HEIGTH)
		drawend = HEIGTH;
	draw_ceiling(s, drawstart - 1, px);
	take_texture(s, drawstart, drawend, px);
	draw_floor(s, drawend - 1, px);
}

void	raycaster(t_map *s, t_ray *ray)
{
	int	px;

	px = 0;
	door_inaccessible(ray);
	ray->mv_angle = (VIEW_ANGLE * PI / 180 / WIDTH);
	while (px < WIDTH)
	{
		ray = init_ray(s, ray, ray->mv_angle, px);
		dda(s, ray, px);
		check_door(s, ray, px);
		minimap_perspective(s, ray);
		draw_stripe(s, ray, ray->raylength, px);
		loop_enemies(s, raycast_enemy);
		px++;
	}
	draw_enemies(s);
	get_shot(s);
}
