
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
	size_t			map_capacity;
	size_t			count;
	t_color			floor;
	t_color			ceiling;
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
int	set_textures(t_map *map, t_map_params *map_params, t_side side, char *path);
int	read_map(t_map *map, t_map_params *map_params, int fd);
int	map_verify(t_map_params *map_params);

//	read_map_utils.c
int	map_params_init(t_map_params *map_params);

//	dentifiers.c
int	get_identifier(t_map *map, t_map_params *map_params, char *str);
int	set_textures(t_map *map, t_map_params *map_params, t_side side, char *path);
int	set_color(t_map *map, t_map_params *map_params, char side, char *str);
int	get_channel(char *str, bool *is_default);
int get_rgba(int r, int g, int b, int a);

#endif
/*
- check closed walls with dfs ?
- atoi for colors ?

commit
"make map_init(), fix get_textures(), parse color's identifier"
*/
