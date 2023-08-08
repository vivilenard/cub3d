
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include "../include/parser.h"
#include "../libft/libft.h"
#include "../MLX42/include/MLX42/MLX42.h"

// where and how are colors using?

int	get_identifier(t_map *map, t_map_params *map_params, char *line)
{
	int			i;
	int			len;
	char		**result;

	i = 0;
	len = ft_strlen(line);
	line[len - 1] = '\0';
	result = ft_split(line, ' ');
	while (result[i])
		i++;
	if (i != 2)
	{
		// free map_init(), result
		;
	}
	else if (ft_strncmp(result[0], "NO\0", 3) == 0 && map->tex[NORTH] == NULL) // need to change for map->tex[]
	{
		// printf("no\n");
		return (set_textures(map, map_params, NORTH, result[1]));
	}
	else if (ft_strncmp(result[0], "SO\0", 3) == 0 && map->tex[SOUTH] == NULL)
	{
		// printf("so\n");
		return (set_textures(map, map_params, SOUTH, result[1]));
	}
	else if (ft_strncmp(result[0], "EA\0", 3) == 0 && map->tex[EAST] == NULL)
	{
		// printf("ea\n");
		return (set_textures(map, map_params, EAST, result[1]));
	}
	else if (ft_strncmp(result[0], "WE\0", 3) == 0 && map->tex[WEST] == NULL)
	{
		// printf("we\n");
		return (set_textures(map, map_params, WEST, result[1]));
	}
	else if (ft_strncmp(result[0], "F\0", 2) == 0 && !map_params->floor.is_color)
	{
		// printf("f\n");
		return (set_color(map, map_params, 'F', result[1]));
	}
	else if (ft_strncmp(result[0], "C\0", 2) == 0 && !map_params->ceiling.is_color)
	{
		// printf("c\n");
		return (set_color(map, map_params, 'C', result[1]));
	}
	// free map_init(), result, colors
	printf("Error: wrong identifier\n");
	return (EXIT_FAILURE);
}

int	set_textures(t_map *map, t_map_params *map_params, t_side side, char *path)
{
	const char	*no_path = "textures/wood.png";
	const char	*so_path = "textures/pillar.png";
	const char	*ea_path = "textures/greystone.png";
	const char	*we_path = "textures/mossy.png";

	map_params->identifier++;
	map->tex[side] = mlx_load_png(path);
	if (map->tex[side] == NULL)
	{
		if (side == NORTH)
			map->tex[side] = mlx_load_png(no_path);
		else if (side == SOUTH)
			map->tex[side] = mlx_load_png(so_path);
		else if (side == EAST)
			map->tex[side] = mlx_load_png(ea_path);
		else if (side == WEST)
			map->tex[side] = mlx_load_png(we_path);
		if (map->tex[side] == NULL)
			return (EXIT_FAILURE);
		else
			printf("Default texture is using\n");
	}
	map->tex[DOOR] = mlx_load_png("./textures/redbrick.png");
	if (map->tex[DOOR] == NULL)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	set_color(t_map *map, t_map_params *map_params, char side, char *str)
{
	int i;
	char	**colors;
	bool	is_default;
	
	i = 0;
	colors = ft_split(str, ',');
	is_default = false;
	while (colors[i])
		i++;
	if (i != 3)
	{
		// free map_init(), colors, result
		printf("Error: wrong identifier\n");
		return (EXIT_FAILURE);
	}
	else if (side == 'F')
	{
		map->floor = get_rgba(
			get_channel(colors[0], &is_default),
			get_channel(colors[1], &is_default),
			get_channel(colors[2], &is_default), 0);
		map_params->floor.is_color = true;
	}
	else if (side == 'C')
	{
		map->ceiling = get_rgba(
			get_channel(colors[0], &is_default),
			get_channel(colors[1], &is_default),
			get_channel(colors[2], &is_default), 0);
		map_params->ceiling.is_color = true;
	}
	map_params->identifier++;
	if (is_default)
		printf("Default color is using\n");
	return (EXIT_SUCCESS);
}

int	get_channel(char *str, bool *is_default)
{
	int	temp;

	temp = ft_atoi(str);
	if (temp > 250 || temp < 0)	
	{
		*is_default = true;
		return (0);
	}
	return (temp);
}

int get_rgba(int r, int g, int b, int a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}
