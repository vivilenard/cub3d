/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlenard <vlenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 12:42:59 by vlenard           #+#    #+#             */
/*   Updated: 2023/07/13 14:19:49 by vlenard          ###   ########.fr       */
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
	parser(argc);
	printf("Height: %d, Width: %d\n", s.map_height, s.map_width);
	print_coordinates(s);
	draw_minimap(&s);
	//raycaster();
	mlx_loop(s.mlx);
	mlx_terminate(s.mlx);
	return (0);
}
