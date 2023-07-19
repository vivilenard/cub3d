/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlenard <vlenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 12:42:59 by vlenard           #+#    #+#             */
/*   Updated: 2023/07/19 12:31:35 by vlenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	full_exit()
{
	exit(0);
}

int main(int argc, char **argv)
{
	t_data s;

	s = init(&s, argv);
	s.img = mlx_new_image(s.mlx, WIDTH, HEIGTH);
	if (mlx_image_to_window(s.mlx, s.img, 0, 0) < 0)
		perror("img to w");
	parser(argc);
	print_coordinates(s);
	draw_minimap(&s);
	raycaster(&s);

	mlx_loop_hook(s.mlx, key_bindings, &s);
	mlx_loop(s.mlx);
	mlx_terminate(s.mlx);
	return (0);
}
// void	raycaster(t_data *s)
// {
// 	double angle;

// 	angle = DR;
// 	int	r = 1;
	
// 	while (r <= 60)
// 	{
// 		init_ray(s, angle, r);
// 		init_dda(s);
// 		dda(s);
// 		ray_dist(s);
// 		to_square(s, s->px + s->rdx * ray_dist(s), s->py + s->rdy * ray_dist(s), 0.05);
// 		draw_line(ray_dist(s), 0);
// 		r++;
// 	}

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
