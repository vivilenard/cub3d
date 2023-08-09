
#ifndef PARSER_H
# define PARSER_H

# include <stdio.h>
# include <stdbool.h>
# include "main.h"

typedef struct s_color
{
	bool	is_color;
	int		red;
	int		green;
	int		blue;
	int		alpha;
	int		color;
}	t_color;

typedef struct s_map_params
{
	t_map_component	**map;
	t_map_component	component;
	mlx_texture_t	*textures[5];
	int				capacity;
	int				count;
	t_color			floor;
	t_color			ceiling;
	int				*all_width;
	int				width;
	int				height;
	int				player;
	int				player_x;
	int				player_y;
	int				doors;
	int				identifier;
	bool			*visited;
}	t_map_params;

//	parser.c
int	parser(t_map *map, t_map_params *map_params, char **argv, int fd);
int	file_path_check(char *argv);
int	quick_exit(char *str, int fd);

//	read_map.c
int	read_map(t_map *map, t_map_params *map_params, int fd);
int get_map(t_map_params *map_params, char *line);
void	map_push(t_map_params *map_params);
void	map_extend(t_map_params *map_params);
t_map_component	convert_char(t_map_params *map_params, char c, int width_position);
// int	map_verify(t_map_params *map_params);
void	print_map(t_map_params *map_params); // delete

//	read_map_utils.c
int	map_init(t_map *map);
int	map_params_init(t_map_params *map_params);

//	dentifiers.c
int	get_identifier(t_map *map, t_map_params *map_params, char *line);
int	set_textures(t_map *map, t_map_params *map_params, t_side side, char *path);
int	set_color(t_map *map, t_map_params *map_params, char side, char *str);
int	get_channel(char *str, bool *is_default); // have to rename
int get_rgba(int r, int g, int b, int a);

#endif
/*
- check closed walls with dfs ?
- store all coordinates (player, c/o doors, enemies)
- give player's view

test case
- empty map
- giant map

commit
"fix wrong map's hight"

		{
			"name": "cub3D",
			"type": "cppdbg",
			"request": "launch",
			"program": "${workspaceFolder}/cub3d/cub3d",
			"args": ["maps/pars_test.cub"],
			"cwd": "${workspaceFolder}/cub3d",
			"MIMode": "lldb"
		},
*/
