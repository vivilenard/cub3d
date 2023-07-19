/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karllenard <karllenard@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 12:42:59 by vlenard           #+#    #+#             */
/*   Updated: 2023/07/19 17:05:43 by karllenard       ###   ########.fr       */
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
