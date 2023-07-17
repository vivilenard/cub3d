/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlenard <vlenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 12:42:59 by vlenard           #+#    #+#             */
/*   Updated: 2023/07/17 17:05:22 by vlenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	full_exit()
{
	exit(0);
}

double	delta_dist(double	side)
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
			if (s->co[s->xmap][s->ymap] == '1')
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
		walldist = s->sidedist_x;
	else
		walldist = s->sidedist_y;
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

void init_ray(t_data *s, double angle, int r)
{
	s->xmap = (int)s->px;
	s->ymap = (int)s->py;
	s->ra = s->pa - angle * 30 + r * angle;
	s->rdx = cos(s->ra);//s->pdx;
	s->rdy = sin(s->ra);//s->pdy;
	s->deltadist_x = delta_dist(s->rdx);
	s->deltadist_y = delta_dist(s->rdy);
	s->hit_side = 0;
}

void	raycaster(t_data *s)
{
	double angle;

	angle = DR;
	int	r = 1;
	
	while (r <= 60)
	{
		init_ray(s, angle, r);
		init_dda(s);
		dda(s);
		ray_dist(s);
		to_square(s, s->px + s->rdx * ray_dist(s), s->py + s->rdy * ray_dist(s), 0.05);
		r++;
		//angle += DR / 30;
	}
	//print details
	// printf("walldist %f\n", ray_dist(s));
	// printf("pdx %f/%f\n", s->rdx, s->rdy);	
	// printf("map %d/%d\n", s->xmap, s->ymap);
	// printf("player %f/%f\n", s->px, s->py);
	// printf("move %d/%d\n", s->xmove, s->ymove);
	printf("deltadist %f/%f\n", delta_dist(s->rdx), delta_dist(s->rdy));
	printf("sidedist %f/%f\n", s->sidedist_x, s->sidedist_y);
}

int main(int argc, char **argv)
{
	t_data s;
	s = init(&s, argv);
	parser(argc);
	printf("Height: %d, Width: %d\n", s.map_height, s.map_width);
	print_coordinates(s);
	draw_minimap(&s);
	raycaster(&s);
	mlx_loop_hook(s.mlx, key_bindings, &s);
	mlx_loop(s.mlx);
	mlx_terminate(s.mlx);
	return (0);
}

	// while (1)
	// {
	// 	if (s->sidedist_x < s->sidedist_y) //? /*yes*/ xmove++ : /*no*/ ymove++);
	// 	{
	// 		if (is_wall(s->sidedist_x))
	// 			return (ray_dist(s->sidedist_x)) ;
	// 		s->sidedist_x += s->xmove;
	// 	}
	// 	else
	// 	{
	// 		if (is_wall(s->ydist))
	// 			break ;
	// 		s->sidedist_y += s->ymove;
	// 	}
	// }
	// return (0);
