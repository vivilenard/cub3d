/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekulichk <ekulichk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 16:16:18 by ekulichk          #+#    #+#             */
/*   Updated: 2023/08/13 16:16:27 by ekulichk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "../include/parser.h"

int	map_init(t_map *map)
{
	int i;

	i = 0;
	while (i != N_TEX)
	{
		map->tex[i] = NULL;
		i++;
	}
	return (EXIT_SUCCESS);
}

int	map_params_init(t_map_params *map_params)
{
	map_params->capacity = 1;
	if (malloc2(sizeof(t_map_char *) * map_params->capacity, (void**) &map_params->map))
		return (print_malloc_failed());
	// map_params->map = malloc(
	// 		sizeof(t_map_char *) * map_params->capacity);
	// if (map_params->map == NULL)
	// 	return (printf("Error: malloc failed\n"), EXIT_FAILURE);
	map_params->map[0] = NULL;
	map_params->all_width = malloc(sizeof(int *) * 1);
	if (map_params->all_width == NULL)
	{
		free(map_params->map);
		return (printf("Error: malloc failed\n"), EXIT_FAILURE);
	}
	map_params->cur_width = 0;
	map_params->max_width = 0;
	map_params->height = 0;
	map_params->player = 0;
	map_params->doors = 0;
	map_params->identifier = 0;
	map_params->map_start = false;
	map_params->map_end = false;
	map_params->floor.is_color = false;
	map_params->ceiling.is_color = false;
	return (EXIT_SUCCESS);
}

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
	if (s->co[x][y] == 'N' || s->co[x][y] == 'S'
		||s->co[x][y] == 'E' ||s->co[x][y] == 'W')
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
	//s->enemy_tex = mlx_load_png("./textures/browndog/103.bmp"); //door

	s->floor = 0x00000000;
	s->ceiling = 0x00000000;
	// check if all textures are valid
	// and check that mlx_load_png was successful (should return NULL if not ?)
}

t_map	init(t_map *s, char **argv) 
{
	s->mlx = mlx_init(WIDTH, HEIGTH, "cub3d", false);
	s->mouse_pos = 0;
	//this is basically all the parsing i did before: (you can overwrite it)
	map_to_koordinate(s, argv[1]);
	scan_coordinates(s, player_position);
	get_textures(s);
	get_enemies(s);
	return (*s);
}









