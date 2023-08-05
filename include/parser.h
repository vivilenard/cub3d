
#ifndef PARSER_H
# define PARSER_H

# include <stdio.h>
# include <stdbool.h>
# include "main.h"

typedef struct s_orintation
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
}	t_orintation;

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
	t_orintation	orintation;
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
int	map_init(t_map_params *map_params);

#endif
/*
- check closed walls with dfs ?

commit
"change main(), add main.h, parse side's identifier"
*/
