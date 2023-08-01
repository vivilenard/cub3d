
#ifndef PARSER_H
# define PARSER_H

# include <stdbool.h>
# include <stdio.h>

typedef enum e_map_component
{
	SPACE,
	WALL,
	PLAYER,
	EXIT,
	OPEN_EXIT,
	ERROR,
}	t_map_component;

typedef struct s_orintation
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
}	t_orintation;

typedef struct s_color
{
	int	red;
	int	green;
	int	blue;
	int	alpha;
	int	color;
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
	int				exit;
	int				exit_x;
	int				exit_y;
	bool			*visited;
}	t_map_params;

//	parser.c
int	parser(int argc, char **argv, t_map_params *map_params, int fd);
int	file_path_check(char *argv);
int	quick_exit(char *str, int fd);

//	read_map.c
int	read_map(t_map_params *map_params, int fd);
int	read_bytes_check(
		t_map_params *map_params, int *read_bytes, int *width_temp, char c);

//	read_map_utils.c
int	map_init(t_map_params *map_params);
int	map_fill_in(
		t_map_params *map_params, char c, int *read_bytes, int *width);

#endif
/*
- implement valid map path in main
- 6 type identifier
if not: add default or trow error
- check closed walls with dfs ?

commit
"change main(), start read_map()"
*/
