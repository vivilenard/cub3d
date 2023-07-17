/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlenard <vlenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 12:42:59 by vlenard           #+#    #+#             */
/*   Updated: 2023/07/17 12:32:10 by vlenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	full_exit()
{
	exit(0);
}

// double	calc_xdist(t_data *s)
// {
// 	double	xdist;

// 	xdist = 0;
// 	//xdist = sqrt(1 + exp(s->rdy / s->rdx));
// 	xdist = fabs(1 / s->rdx);
// 	return (xdist);
// }

double	delta_dist(double	side)
{
	// if (side == 0)
	// 	return ((double)1e30);
	return (fabs(1 / side));
}

// double	dda(t_data *s)
// {
// 	//init_dda(s);
// 	while (1)
// 	{
// 		s->xdist = calc_xdist(s);
// 		s->ydist = calc_ydist();
// 		if (s->xdist < s->ydist) //? /*yes*/ xmove++ : /*no*/ ymove++);
// 		{
// 			if (is_wall(s->xdist))
// 				return (ray_dist(s->xdist)) ;
// 			s->sidedist_x += s->xmove;
// 		}
// 		else
// 		{
// 			if (is_wall(s->ydist))
// 				break ;
// 			s->sidedist_y += s->ymove;
// 		}
// 	}
// 	return (0);
// }

int	orientation(double v)
{
	if (v < 0)
		return (-1);
	return (1);
}

void	raycaster(t_data *s)
{
	//double	raydist = 0;
	//s->ra = s->pa;
	s->rdx = s->pdx;
	s->rdy = s->pdy;
	s->xmap = (int)s->px;
	s->ymap = (int)s->py;
	s->xmove = orientation(s->rdx);
	s->ymove = orientation(s->rdy);
	s->deltadist_x = delta_dist(s->rdx);
	s->deltadist_y = delta_dist(s->rdy);
	
	s->sidedist_x = delta_dist(s->rdx) * (((double)(s->xmap + 1) - s->px));
	s->sidedist_y = delta_dist(s->rdy) * (((double)(s->ymap + 1)) - s->py);

	//dda(s);


	//print details
	printf("map %d/%d\n", s->xmap, s->ymap);
	printf("pdx %f/%f\n", s->pdx, s->pdy);	
	printf("player %f/%f\n", s->px, s->py);
	printf("move %d/%d\n", s->xmove, s->ymove);
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
