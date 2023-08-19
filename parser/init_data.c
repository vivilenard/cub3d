/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekulichk <ekulichk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 16:16:18 by ekulichk          #+#    #+#             */
/*   Updated: 2023/08/19 13:10:56 by ekulichk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "../include/parser.h"

int	map_params_init(t_map_params *map_params)
{
	map_params->capacity = 1;
	map_params->map = malloc(
			sizeof(t_map_char *) * map_params->capacity);
	if (map_params->map == NULL)
		return (printf("Error: malloc failed\n"), EXIT_FAILURE);
	map_params->map[0] = NULL;
	map_params->all_width = malloc(sizeof(int *) * 1);
	if (map_params->all_width == NULL)
	{
		free(map_params->map);
		return (printf("Error: malloc failed\n"), EXIT_FAILURE);
	}
	tex_init(map_params);
	map_params->floor.is_color = false;
	map_params->ceiling.is_color = false;
	map_params->max_width = 0;
	map_params->height = 0;
	map_params->player = 0;
	map_params->doors = 0;
	map_params->identifier = 0;
	map_params->map_start = false;
	map_params->map_end = false;
	return (EXIT_SUCCESS);
}

void	tex_init(t_map_params *map_params)
{
	map_params->textures.no = NULL;
	map_params->textures.so = NULL;
	map_params->textures.ea = NULL;
	map_params->textures.we = NULL;
}

double	init_player_view(char c)
{
	if (c == 'N')
		return (PI * 3 / 2);
	if (c == 'E')
		return (2 * PI);
	if (c == 'S')
		return (PI / 2);
	if (c == 'W')
		return (PI);
	return (0);
}

// maybe
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

// don't need it later
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
	s->tex[5] = mlx_load_png("./textures/a7.png"); //enemy
	s->tex[6] = NULL;
	//s->enemy_tex = mlx_load_png("./textures/browndog/103.bmp"); //door

	s->floor = 0x00000000;
	s->ceiling = 0x00000000;
	// check if all textures are valid
	// and check that mlx_load_png was successful (should return NULL if not ?)
}

t_map	init(t_map *s, char **argv) 
{
	(void) argv;
	printf("init\n");
	s->mlx = mlx_init(WIDTH, HEIGTH, "cub3d", false);
	if (!s->mlx)
		full_exit();
	s->mouse_pos = 0;
	//this is basically all the parsing i did before: (you can overwrite it)
	// map_to_koordinate(s, argv[1]);
	// scan_coordinates(s, player_position);
	//get_textures(s);
	get_enemies(s);
	return (*s);
}









