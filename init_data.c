/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlenard <vlenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 17:53:23 by vlenard           #+#    #+#             */
/*   Updated: 2023/07/13 14:19:33 by vlenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	set_player(t_data *s, int x, int y)
{
	printf("set player here: %d/%d\n", x, y);
	s->px = (double)x;
	s->py = (double)y;
	return (1);
}

int	player_position(t_data *s, int x, int y)
{
	if (ft_isalpha(s->co[x][y]))
		return (set_player(s, x, y), 1);
	return (0);
}

t_data	init(t_data *s, char **argv)
{
	s = malloc(sizeof(t_data));
	s->mlx = mlx_init(WIDTH, HEIGTH, "cub3d", false);
	map_to_koordinate(s, argv[1]);
	//printf ("%d, %d\n", s->map_height, s->map_width);
	scan_coordinates(s, player_position);
	return (*s);
}
