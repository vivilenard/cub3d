
#include "../include/parser.h"
#include "../include/main.h"
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <math.h>
#include "../libft/libft.h"

int	parser(t_map_params *map_params, t_map *map, char **argv, int fd)
{
	if (!file_path_check(argv[1]))
		return (quick_exit(
				"Error: wrong file, expected a map in format *.cub\n", fd));
	if (map_params_init(map_params))
		return (EXIT_FAILURE);
	if (read_map(map_params, fd))
	{
		return (EXIT_FAILURE);
	}
	if (map_params->map[0] == NULL)
		return (printf("Error: map is empty\n"), EXIT_FAILURE);
	if (zero_extend(map_params))
		return (EXIT_FAILURE);
	if (map_verify(map_params))
		return (EXIT_FAILURE);
	// print_map_params(map_params);
	if (fill_in_t_map(map_params, map))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	fill_in_t_map(t_map_params *map_params, t_map *map)
{
	int	i;

	i = 0;
	map->co = map_params->map;
	map_params->map = NULL;
	// while (i != 4)
	// {
	// 	map->tex[i] = map_params->textures.texs[i];
	// 	i++;
	// }
	// map->tex[DOOR] = mlx_load_png("./textures/redbrick.png");
	// map->tex[5] = mlx_load_png("./textures/zombie0.png");
	// if (map->tex[DOOR] == NULL
	// 	|| map->tex[5] == NULL)
	// 	return (EXIT_FAILURE);
	// map->tex[6] = NULL;
	map->map_height = map_params->height;
	map->map_width = map_params->max_width;
	map->px = (double) map_params->player_x + 0.5;
	map->py = (double) map_params->player_y + 0.5;
	map->pa = map_params->player_view;
	map->pdx = cos(map->pa);
	map->pdy = sin(map->pa);
	map->p_radius = 0.09;
	map->mouse_pos = 0;
	// map->floor = map_params->floor.color;
	// map->ceiling = map_params->ceiling.color;
	map->floor = 0xFF0000FF;
	map->ceiling = 0xFF0000FF;
	map->co[map_params->player_y][map_params->player_x] = SPACE;
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

int	zero_extend(t_map_params *map_params)
{
	int			i;
	int			i_height;
	t_map_char	*new_line;

	i = 0;
	i_height = 0;
	while (i_height < map_params->height)
	{
		if (map_params->all_width[i_height] < map_params->max_width
			|| i_height + 1 >= map_params->height)
		{
			new_line = ft_calloc(map_params->max_width + 1, sizeof(t_map_char));
			if (new_line == NULL)
				return (EXIT_FAILURE);
			ft_memcpy(new_line, map_params->map[i_height],
				map_params->all_width[i_height] * sizeof(t_map_char));
			free(map_params->map[i_height]);
			map_params->map[i_height] = new_line;
		}
		i_height++;
	}
	map_params->map[map_params->height - 1][map_params->max_width] = TERMINAL;
	return (EXIT_SUCCESS);
}
