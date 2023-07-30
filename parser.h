
#ifndef PARSER_H
# define PARSER_H

# include <stdbool.h>
# include <stdio.h>

typedef enum e_map_component
{
	SPACE,
	WALL,
	PLAYER,
	// EXIT,
	// OPEN_EXIT,
	// COLLECTIBLE,
	ERROR,
}	t_map_component;

// typedef struct s_exit_enemy
// {
// 	int				exit;
// 	int				exit_x;
// 	int				exit_y;
// 	int				enemy_x;
// 	int				enemy_y;
// }	t_exit_enemy;

typedef struct s_map_params
{
	t_map_component	*map;
	t_map_component	component;
	size_t			map_capacity;
	size_t			count;
	int				width;
	int				height;
	int				player;
	int				player_x;
	int				player_y;
	bool			*visited;
	// int				sprite_index;
	// t_map_render	*map_render;
}	t_map_params;

//      parser.c
int		parser(int argc, char **argv);

#endif
/*
- implement valid map path in main

- 6 type identifier
if not: add default or trow error

- check enclosed walls with dfs ?

- check if file was closed succsessfuly?
*/

/*
commit
"check valid fd, check valid map path"
*/
