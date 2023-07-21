/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlenard <vlenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 17:53:23 by vlenard           #+#    #+#             */
/*   Updated: 2023/07/21 16:54:26 by vlenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

int	set_player(t_data *s, int x, int y)
{
	s->px = (double)x + 0.5;
	s->py = (double)y + 0.5;
	s->pa = init_player_view(s->co[x][y]);
	s->pdx = cos(s->pa);
	s->pdy = sin(s->pa);
	s->p_radius = 0.09;
	return (1);
}

int	player_position(t_data *s, int x, int y)
{
	if (ft_isalpha(s->co[x][y]))
		return (set_player(s, x, y), 1);
	return (0);
}

void	get_textures(t_data *s)
{
	s->tex[0] = mlx_load_png("./textures/wood.png");	//no
	s->tex[1] = mlx_load_png("./textures/pillar.png");	//so
	s->tex[2] = mlx_load_png("./textures/greystone.png");	//east
	s->tex[3] = mlx_load_png("./textures/mossy.png");	//west
	s->tex[4] = NULL;
	// check if all textures are valid
}

t_data	init(t_data *s, char **argv)
{
	s = malloc(sizeof(t_data));
	s->mlx = mlx_init(WIDTH, HEIGTH, "cub3d", false);
	map_to_koordinate(s, argv[1]);
	scan_coordinates(s, player_position);
	get_textures(s);
	return (*s);
}









