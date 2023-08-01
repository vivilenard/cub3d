/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlenard <vlenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 10:51:37 by vlenard           #+#    #+#             */
/*   Updated: 2023/08/01 17:47:15 by vlenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
			if (s->co[r->xmap][r->ymap] == WALL)
				break ;
			r->sidedist_x += r->deltadist_x;
		}
		else
		{
			r->ymap += r->ymove;
			r->hit_side = 1;
		if (s->co[r->xmap][r->ymap] == WALL)
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

t_ray	*init_ray(t_map *s, double angle, int r)
{
	t_ray *ray;

	ray = malloc(sizeof(t_ray));
	s->ray = ray;
	
	ray->ra = s->pa - angle * WIDTH / 2 + r * angle;
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
	return (ray);
}


void	draw_stripe(t_map *s, t_ray *r, double dist, int px)
{
	int	drawstart;
	int drawend;

	r->lineheight = HEIGTH / dist;
	drawstart = HEIGTH / 2 - r->lineheight / 2;
	if (drawstart < 0)
		drawstart = 0;
	drawend = HEIGTH / 2 + r->lineheight / 2;
	if (drawend >= HEIGTH)
		drawend = HEIGTH - 1;
	take_texture(s, drawstart, drawend, px);
	
}

void	minimap_perspective(t_map *s, t_ray *ray)
{
	double	x;
	double	y;
	double	pixel_x;
	double	pixel_y;
	int		pixels;

	x = (ray->hit_x - s->px) * s->mm_square;
	y = (ray->hit_y - s->py) * s->mm_square;
	pixels = (sqrt((x * x) + (y * y)));
	x /= pixels;
	y /= pixels;
	pixel_x = s->px * s->mm_square;
	pixel_y = s->py * s->mm_square;
	while (pixels)
	{
		mlx_put_pixel(s->minimap, (int)(pixel_x) , (int)(pixel_y), 0xFF0000FF);
		pixel_x += x;
		pixel_y += y;
		--pixels; 
	}
	//to_square(s, ray->hit_x, ray->hit_y, 0.05);
}

void	raycaster(t_map *s)
{
	t_ray	*ray;
	double angle;

	angle = 1.15 / WIDTH;  //1.15 ~ 66 degree
	int	px = 0;
	
	memset(s->img->pixels, 255, s->img->width * s->img->height * sizeof(int32_t));
	while (px < WIDTH)
	{
		ray = init_ray(s, angle, px);
		init_dda(s, ray);
		dda(s, ray);
		minimap_perspective(s, ray);
		draw_stripe(s, ray, ray_dist(s, ray) * cos(s->pa - ray->ra) , px);
		px++;
	}
	if (mlx_image_to_window(s->mlx, s->img, 0, 0) < 0)
		perror("img to w");
}





	//print details
	// printf("pdx %f/%f\n", s->rdx, s->rdy);	
	// printf("map %d/%d\n", s->xmap, s->ymap);
	// printf("player %f/%f\n", s->px, s->py);
	// printf("move %d/%d\n", s->xmove, s->ymove);
	//printf("deltadist %f/%f\n", delta_dist(s->rdx), delta_dist(s->rdy));
	//printf("sidedist %f/%f\n", s->sidedist_x, s->sidedist_y);