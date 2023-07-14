/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karllenard <karllenard@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 12:42:59 by vlenard           #+#    #+#             */
/*   Updated: 2023/07/14 13:44:41 by karllenard       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	full_exit()
{
	exit(0);
}

void	key_bindings(void *p)
{
	t_data *s;

	s = (t_data *) p;
	if (mlx_is_key_down(s->mlx, MLX_KEY_ESCAPE))
	{
		mlx_terminate(s->mlx);
		exit(EXIT_SUCCESS);
	}
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
	mlx_loop_hook(s.mlx, key_bindings, &s);
	mlx_loop(s.mlx);
	mlx_terminate(s.mlx);
	return (0);
}
