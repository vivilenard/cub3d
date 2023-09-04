/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekulichk <ekulichk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 17:07:39 by ekulichk          #+#    #+#             */
/*   Updated: 2023/09/04 13:17:33 by ekulichk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stdio.h>
# include <stdbool.h>
# include "cub3d.h"
# include "../MLX42/include/MLX42/MLX42.h"

typedef struct s_color_set
{
	bool		is_color;
	uint32_t	color;
}	t_color_set;

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
	t_color_set		floor;
	t_color_set		ceiling;
	t_textures		textures;
	int				identifier;
	int				player;
	int				player_x;
	int				player_y;
	double			player_view;
	bool			map_start;
	bool			map_end;
	bool			*visited;
}	t_map_set;

//	parser.c +[]
int			parser(t_map_set *map_set, t_map *map, char **argv, int fd);
void		fill_in_t_map(t_map_set *map_set, t_map *map);
int			file_path_check(char *argv);
int			quick_exit(char *str, int fd);

//	read_map.c +[]
int			read_map(t_map_set *map_set, int fd);
int			proceed_line(t_map_set *map_set, char *line);
int			zero_extend(t_map_set *map_set);

//	create_map.c +
int			create_map(t_map_set *map_set, char *line);
int			extention(t_map_set *map_set);
int			map_extend(t_map_set *map_set);
int			all_width_extend(t_map_set *map_set);
t_map_char	convert_char(t_map_set *map_set, char c, int width);

//	identifiers.c +[]
int			get_identifier(t_map_set *map_set, char *line);
int			set_identifier(t_map_set *map_set, char **result);
char		*iden_copy(char *src);

//	color.c +[]
int			get_color(t_map_set *map_set, char side, char *str);
void		set_color(
				t_map_set *map_set, char side, char **colors, bool *is_default);
int			get_channel(char *str, bool *is_default);
int			get_rgba(int r, int g, int b, int a);

//	map_verify.c +
int			map_verify(t_map_set *map_set);
int			visited_init(t_map_set *map_set);
bool		dfs(t_map_set *map_set, int y, int x);
bool		is_visited(t_map_set *map_set, int y, int x);
void		set_visited(t_map_set *map_set, int y, int x);

//	init_data.c +
int			map_set_init(t_map_set *map_set);
void		tex_init(t_map_set *map_set);
double		init_player_view(char p);
int			set_textures(t_map_set *map_set, t_map *map);
int			check_textures(t_map *map);

//	parser_utils.c
void		free_split(char **str, int i);
void		free_map_set(t_map_set *map_set);
void		free_sides(t_map_set *map_set);
int			free_if_error(t_map_set *map_set);
int			print_malloc_failed(void);

#endif
