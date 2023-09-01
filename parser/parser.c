
#include "../include/parser.h"
#include "../include/cub3d.h"
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <math.h>
#include "../libft/libft.h"

int	parser(t_map_set *map_set, t_map *map, char **argv, int fd)
{
	if (!file_path_check(argv[1]))
		return (quick_exit(
				"Error: wrong file, expected a map in format *.cub\n", fd));
	if (map_set_init(map_set))
		return (EXIT_FAILURE);
	if (read_map(map_set, fd))
	{
		free_sides(map_set);
		free_map_set(map_set);
		return (EXIT_FAILURE);
	}
	if (map_set->map[0] == NULL)
	{
		free_sides(map_set);
		free_map_set(map_set);
		return (printf("Error: map is empty\n"), EXIT_FAILURE);
	}
	if (zero_extend(map_set))
	{
		free_sides(map_set);
		free_map_set(map_set);
		return (EXIT_FAILURE);
	}
	if (map_verify(map_set))
		return (EXIT_FAILURE);
	// print_map_set(map_set);
	if (fill_in_t_map(map_set, map))
		return (EXIT_FAILURE);
	free(map_set->all_width);
	return (EXIT_SUCCESS);
}

int	fill_in_t_map(t_map_set *map_set, t_map *map)
{
	map->co = map_set->map;
	map_set->map = NULL;
	// map->enemy = map_set->enemies;
	// map_set->enemies = NULL;
	// while (i != 4)
	// {
	// 	map->tex[i] = map_set->textures.texs[i];
	// 	i++;
	// }
	// map->tex[DOOR] = mlx_load_png("./textures/redbrick.png");
	// map->tex[5] = mlx_load_png("./textures/zombie0.png");
	// if (map->tex[DOOR] == NULL
	// 	|| map->tex[5] == NULL)
	// 	return (EXIT_FAILURE);
	// map->tex[6] = NULL;
	map->map_height = map_set->height;
	map->map_width = map_set->max_width;
	map->px = (double) map_set->player_x + 0.5;
	map->py = (double) map_set->player_y + 0.5;
	map->pa = map_set->player_view;
	map->pdx = cos(map->pa);
	map->pdy = sin(map->pa);
	map->p_radius = 0.09;
	map->mouse_pos = 0;
	map->floor = map_set->floor.color;
	map->ceiling = map_set->ceiling.color;
	map->co[map_set->player_y][map_set->player_x] = SPACE;
	map->lives = LIVES;
	return (EXIT_SUCCESS);
}

int	file_path_check(char *argv)
{
	int		i;
	int		len;
	char	*cub;

	i = 0;
	cub = ".cub";
	len = ft_strlen(argv) - 4;
	while (i != 5)
	{
		if (argv[len + i] != cub[i])
			return (EXIT_SUCCESS);
		i++;
	}
	return (EXIT_FAILURE);
}

int	quick_exit(char *str, int fd)
{
	printf("%s", str);
	close(fd);
	return (EXIT_FAILURE);
}

int	zero_extend(t_map_set *map_set)
{
	int			i_height;
	t_map_char	*new_line;

	i_height = 0;
	while (i_height < map_set->height)
	{
		if (map_set->all_width[i_height] < map_set->max_width
			|| i_height + 1 >= map_set->height)
		{
			new_line = ft_calloc(map_set->max_width + 1, sizeof(t_map_char));
			if (new_line == NULL)
				return (EXIT_FAILURE);
			ft_memcpy(new_line, map_set->map[i_height],
				map_set->all_width[i_height] * sizeof(t_map_char));
			free(map_set->map[i_height]);
			map_set->map[i_height] = new_line;
		}
		i_height++;
	}
	map_set->map[map_set->height - 1][map_set->max_width] = TERMINAL;
	return (EXIT_SUCCESS);
}
