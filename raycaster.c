/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlenard <vlenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 10:51:37 by vlenard           #+#    #+#             */
/*   Updated: 2023/07/19 12:49:11 by vlenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	delta_dist(double side)
{
	return (fabs(1 / side));
}

double	dda(t_data *s)
{
	while (1)
	{
		if (s->sidedist_x < s->sidedist_y)
		{
			s->xmap += s->xmove;
			s->hit_side = 0;
			if (s->co[s->xmap][s->ymap] == '1') //is_wall
				break ;
			s->sidedist_x += s->deltadist_x;
		}
		else
		{
			s->ymap += s->ymove;
			s->hit_side = 1;
		if (s->co[s->xmap][s->ymap] == '1')
			break ;
			s->sidedist_y += s->deltadist_y;
		}
	}
	// if (side = 0)
	// 	Walldist = s->sidedist_x - s->deltadist_x;
	// else
	// 	Walldist = s->sidedist_y - s->deltadist_y;
	return (0);
}


double	ray_dist(t_data *s)
{
	double	walldist;

	if (s->hit_side == 0)
	{
		walldist = s->sidedist_x;
		s->perp_walldist = walldist - s->deltadist_x;
	}
	else
	{
		walldist = s->sidedist_y;
		s->perp_walldist = walldist - s->deltadist_y;
	}
	return (walldist);
}

void	init_dda(t_data *s)
{
	if (s->rdx < 0)
	{
		s->xmove = -1;
		s->sidedist_x = delta_dist(s->rdx) * ((double)(s->px - s->xmap));
	}
	else
	{
		s->xmove = 1;
		s->sidedist_x = delta_dist(s->rdx) * ((double)(s->xmap + 1) - s->px);
	}
	if (s->rdy < 0)
	{
		s->ymove = -1;
		s->sidedist_y = delta_dist(s->rdy) * ((double)(s->py - s->ymap));
	}
	else
	{
		s->ymove = 1;
		s->sidedist_y = delta_dist(s->rdy) * ((double)(s->ymap + 1) - s->py);
	}
}

void	init_ray(t_data *s, double angle, int r)
{
	s->xmap = (int)s->px;
	s->ymap = (int)s->py;
	s->ra = s->pa - angle * WIDTH / 2 + r * angle;
	s->rdx = cos(s->ra);//s->pdx;
	s->rdy = sin(s->ra);//s->pdy;
	s->deltadist_x = delta_dist(s->rdx);
	s->deltadist_y = delta_dist(s->rdy);
	s->perp_walldist = 0;
	s->hit_side = 0;
}

void	to_vert_line(mlx_image_t *img, int p1, int p2, int px)
{
	int	start = p1;
	int	end = p2;

	if (p2 < p1)
	{
		start = p2;
		end = p1;
	}
	while (start < end)
	{
		mlx_put_pixel(img, px, start, 0xffff00ff);
		start++;
	}
	
}

void	draw_line(mlx_image_t *img, double dist, int px)
{
	int	lineheight;
	int	drawstart;
	int drawend;

	lineheight = HEIGTH / dist;
	drawstart = HEIGTH / 2 - lineheight / 2;
	if (drawstart < 0)
		drawstart = 0;
	drawend = HEIGTH / 2 + lineheight / 2;
	if (drawend >= HEIGTH)
		drawend = HEIGTH - 1;
	to_vert_line(img, drawstart, drawend, px);
	
}

void	raycaster(t_data *s)
{
	double angle;

	angle = 1.15 / WIDTH;
	int	px = 0;

	memset(s->img->pixels, 255, s->img->width * s->img->height * sizeof(int32_t));
	while (px < WIDTH)
	{
		init_ray(s, angle, px);
		init_dda(s);
		dda(s);
		ray_dist(s);
		to_square(s, s->px + s->rdx * ray_dist(s), s->py + s->rdy * ray_dist(s), 0.05);
		draw_line(s->img, ray_dist(s), px);
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