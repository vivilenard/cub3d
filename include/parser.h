
#ifndef PARSER_H
# define PARSER_H

# include <stdio.h>
# include <stdbool.h>
# include "main.h"
# include "../MLX42/include/MLX42/MLX42.h"

typedef struct s_color
{
	bool		is_color;
	uint32_t	color;
}	t_color;

typedef struct s_textures
{
	char	*no;
	char	*so;
	char	*ea;
	char	*we;
	mlx_texture_t	*texs[N_TEX];
	mlx_texture_t   *enemy;
}	t_textures;

typedef struct s_map_params
{
	t_map_char		**map;
	int				capacity;
	t_map_char		component;
	int				max_width;
	int				*all_width;
	int				height;
	t_color			floor;
	t_color			ceiling;
	t_textures		textures;
	int				identifier;
	int				player;
	int				player_x;
	int				player_y;
	double			player_view;
	int				doors;
	bool			map_start;
	bool			map_end;
	bool			*visited;
}	t_map_params;

//	parser.c
int	parser(t_map_params *map_params, t_map *map, char **argv, int fd);
int	fill_in_t_map(t_map_params *map_params, t_map *map);
int	file_path_check(char *argv);
int	quick_exit(char *str, int fd);
int	zero_extend(t_map_params *map_params);

//	read_map.c
int	read_map(t_map_params *map_params, int fd);
void	print_map_params(t_map_params *map_params); // delete

//	read_map_utils.c
int get_map(t_map_params *map_params, char *line);
int	map_extend(t_map_params *map_params);
t_map_char	convert_char(t_map_params *map_params, char, int width);

//	identifiers.c
int	get_identifier(t_map_params *map_params, char *line);
int	set_iden(t_map_params *map_params, char **result);
int	set_textures(t_map_params *map_params);
int	set_color(t_map_params *map_params, char side, char *str);
int	get_channel(char *str, bool *is_default); // have to rename
int get_rgba(int r, int g, int b, int a);
void	free_split(char **str, int i);

//	map_verify.c
int	map_verify(t_map_params *map_params);

//	init_data.c
void	tex_init(t_map_params *map_params);
int	map_params_init(t_map_params *map_params);
double	init_player_view(char p);

#endif
/*
- change get_id (if have only ID)
- init_map make after get all map
- check empty map (change error message)
- enemy struct
- store all coordinates (player, c/o doors, enemies)

test case
- empty map
- giant map

commit
""


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
