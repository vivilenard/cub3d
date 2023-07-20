/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlenard <vlenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 10:51:37 by vlenard           #+#    #+#             */
/*   Updated: 2023/07/20 14:48:04 by vlenard          ###   ########.fr       */
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
	s->hit_x = s->px + s->rdx * ray_dist(s);
	s->hit_y = s->py + s->rdy * ray_dist(s);
	return (0);
}


double	ray_dist(t_data *s)
{
	if (s->hit_side == 0)
		return (s->sidedist_x);
	return (s->sidedist_y);
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
	s->hit_side = 0;
	s->hit_x = 0;
	s->hit_y = 0;
}

void	to_vert_line(t_data *s, int p1, int p2, int px)
{
	int	color;
	int	start = p1;
	int	end = p2;

	color = 0xffff00ff;
	if (p2 < p1)
	{
		start = p2;
		end = p1;
	}
	while (start < end)
	{
		if (s->hit_side == 1)
			color = 0xff0000ff;
		mlx_put_pixel(s->img, px, start, color);
		start++;
	}
	
}

int	choose_texture(t_data *s)
{
	int	wall_side;
	
	if (s->hit_side = 0) //side x
	{
		if (s->pdx > 0)
			wall_side = 3;//west
		else
			wall_side = 2;//east
	}
	else if (s->hit_side = 1)
	{
		if (s->pdy < 0)
			wall_side = 0;//no
		else
			wall_side = 1;//so
	}
	
	return (wall_side);
}

int		texture_color(mlx_texture_t *txt, int y)
{

}

void	print_texture(t_data *s, int p1, int p2, int px)
{
	int wall_side;
	int	color;
	int	start = p1;
	int	end = p2;
	double	wall_x;
	int	tex_x;
	int	tex_width;
	int	tex_height;

	wall_side = choose_texture(s);
	//tex_width = get_tex_width(s, choose_texture(s));
	wall_x = s->hit_x - (int)s->hit_x;
	if ((s->hit_side) == 0)
		wall_x = s->hit_y - (int)s->hit_y;
	tex_x = (int)wall_x * s->tex[wall_side]->width;
	if (p2 < p1)
	{
		start = p2;
		end = p1;
	}
	tex_height = s->tex[wall_side]->height;
	s->tex_step = tex_height / (end - start);
	s->tex_pos = (start - HEIGTH / 2 + (end - start) / 2) * s->tex_step ; //this is right
	//s->tex_pos = (end - start) * 
	while (start < end)
	{
		// if (s->hit_side == 1)
		// 	color = texture_color(s->tex[wall_side], start);
		mlx_put_pixel(s->img, px, start, s->tex[wall_side][tex_height * (int)s->tex_pos + tex_x]);
		start++;
		s->tex_pos += s->tex_step;
	}
}

void	draw_line(t_data *s, double dist, int px)
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
	//to_vert_line(s, drawstart, drawend, px);
	print_texture(s, drawstart, drawend, px);
	
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
		to_square(s, s->hit_x, s->hit_y, 0.05);
		draw_line(s, ray_dist(s) * cos(s->pa - s->ra) , px);
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