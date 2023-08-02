/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlenard <vlenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 17:53:23 by vlenard           #+#    #+#             */
/*   Updated: 2023/07/31 13:36:07 by vlenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

double	init_player_view(char p)
{
	if (p == 'N')
		return (PI * 3 / 2);
	if (p == 'E')
		return (2 * PI);
	if (p == 'S')
		return (PI / 2);
	if (p == 'W')
		return (PI);
	return (0);
}

int	set_player(t_map *s, int x, int y)
{
	s->px = (double)x + 0.5;
	s->py = (double)y + 0.5;
	s->pa = init_player_view(s->co[x][y]);
	s->pdx = cos(s->pa);
	s->pdy = sin(s->pa);
	s->p_radius = 0.09;
	return (1);
}

int	player_position(t_map *s, int x, int y)
{
	if (ft_isalpha(s->co[x][y]))
		return (set_player(s, x, y), 1);
	return (0);
}

void	get_textures(t_map *s)
{
	s->tex[0] = mlx_load_png("./textures/wood.png");	//no
	s->tex[1] = mlx_load_png("./textures/pillar.png");	//so
	s->tex[2] = mlx_load_png("./textures/greystone.png");	//east
	s->tex[3] = mlx_load_png("./textures/mossy.png");	//west
	s->tex[4] = mlx_load_png("./textures/redbrick.png"); //door
	s->tex[5] = NULL;
	// check if all textures are valid
	// and check that mlx_load_png was successful (should return NULL if not ?)
}

t_map	init(t_map *s, char **argv)
{
	s->mlx = mlx_init(WIDTH, HEIGTH, "cub3d", false);
	s->mouse_pos = 0;
	//this is basically all the parsing i did before
	map_to_koordinate(s, argv[1]);
	scan_coordinates(s, player_position);
	get_textures(s);
	return (*s);
}









