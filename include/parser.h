
#ifndef PARSER_H
# define PARSER_H

# include <stdio.h>
# include <stdbool.h>
# include "cub3d.h"
# include "../MLX42/include/MLX42/MLX42.h"

typedef struct s_color
{
	bool		is_color;
	uint32_t	color;
}	t_color;

typedef struct s_textures
{
	char			*no;
	char			*so;
	char			*ea;
	char			*we;
}	t_textures;

typedef struct s_map_settings
{
	t_map_char		**map;
	int				map_capacity;
	t_map_char		component;
	int				max_width;
	int				height;
	int				*all_width;
	int				width_capacity;
	t_color			floor;
	t_color			ceiling;
	t_textures		textures;
	int				identifier;
	int				player;
	int				player_x;
	int				player_y;
	double			player_view;
	int				doors; // ?
	bool			map_start;
	bool			map_end;
	bool			*visited;
}	t_map_set;

//	parser.c
int	parser(t_map_set *map_set, t_map *map, char **argv, int fd);
int	fill_in_t_map(t_map_set *map_set, t_map *map);
int	file_path_check(char *argv);
int	quick_exit(char *str, int fd);
int	zero_extend(t_map_set *map_set);

//	read_map.c
int	read_map(t_map_set *map_set, int fd);
int	proceed_line(t_map_set *map_set, char *line);
void	print_map_set(t_map_set *map_set); // delete

//	create_map.c
int get_map(t_map_set *map_set, char *line);
int	map_extend(t_map_set *map_set);
t_map_char	convert_char(t_map_set *map_set, char, int width);

//	identifiers.c
int	get_identifier(t_map_set *map_set, char *line);
int	set_identifier(t_map_set *map_set, char **result);
int	set_textures(t_map_set *map_set, t_map *map);
void	free_split(char **str, int i);
void	free_map_set(t_map_set *map_set);
void	free_sides(t_map_set *map_set);

//	color.c
int	get_color(t_map_set *map_set, char side, char *str);
void	set_color(t_map_set *map_set, char side, char **colors, bool *is_default);
int	get_channel(char *str, bool *is_default);
int get_rgba(int r, int g, int b, int a);

//	map_verify.c
int	map_verify(t_map_set *map_set);
int	visited_init(t_map_set *map_set);
bool	dfs(t_map_set *map_set, int y, int x);
bool	is_visited(t_map_set *map_set, int y, int x);
void	set_visited(t_map_set *map_set, int y, int x);

//	init_data.c
void	tex_init(t_map_set *map_set);
int	map_set_init(t_map_set *map_set);
double	init_player_view(char p);

//	parser_utils.c
int	print_malloc_failed(void);

#endif

/*
- remove heart_red_black and gun textures
- check why textures are invalid

commit
"fix leaks"


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

// struct s_dynamic_array
// {
// 	void	*bufffer;
// 	int		size;
// 	int		capacity;
// 	int		item_size;
// };
