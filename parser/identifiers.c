
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include "../include/parser.h"
#include "../libft/libft.h"
#include "../MLX42/include/MLX42/MLX42.h"

int	get_identifier(t_map_params *map_params, char *line)
{
	int			i;
	int			len;
	char		**result;

	i = 0;
	len = ft_strlen(line);
	if (len >= 2)
		line[len - 1] = '\0';
	else
		return (printf("Error: wrong identifier\n"), EXIT_FAILURE);
	result = ft_split(line, ' ');
	if (result == NULL)
		return (printf("Error: wrong identifier\n"), EXIT_FAILURE);
	while (result[i])
		i++;
	if (i != 2 || set_iden(map_params, result))
		return (free_split(result, i),
			printf("Error: wrong identifier\n"), EXIT_FAILURE);
	free(result[0]);
	free(result);
	map_params->identifier++;
	return (EXIT_SUCCESS);
}

int	set_iden(t_map_params *map_params, char **result)
{
	if (ft_strncmp(result[0], "NO\0", 3) == 0 && map_params->textures.no == NULL)
		map_params->textures.no = result[1];
	else if (ft_strncmp(result[0], "SO\0", 3) == 0
		&& map_params->textures.so == NULL)
		map_params->textures.so = result[1];
	else if (ft_strncmp(result[0], "EA\0", 3) == 0
		&& map_params->textures.ea == NULL)
		map_params->textures.ea = result[1];
	else if (ft_strncmp(result[0], "WE\0", 3) == 0
		&& map_params->textures.we == NULL)
		map_params->textures.we = result[1];
	else if (ft_strncmp(result[0], "F\0", 2) == 0 && !map_params->floor.is_color)
	{
		if (set_color(map_params, 'F', result[1]))
			return (EXIT_FAILURE);
	}
	else if (ft_strncmp(result[0], "C\0", 2) == 0
		&& !map_params->ceiling.is_color)
	{
		if (set_color(map_params, 'C', result[1]))
			return (EXIT_FAILURE);
	}
	else
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	set_textures(t_map_params *map_params)
{
	int			i;
	const char	*side[4];

	i = 0;
	side[NORTH] = "textures/wood.png";
	side[SOUTH] = "textures/pillar.png";
	side[EAST] = "textures/mossy.png";
	side[WEST] = "textures/greystone.png";
	map_params->textures.texs[NORTH] = mlx_load_png(map_params->textures.no);
	map_params->textures.texs[SOUTH] = mlx_load_png(map_params->textures.so);
	map_params->textures.texs[EAST] = mlx_load_png(map_params->textures.ea);
	map_params->textures.texs[WEST] = mlx_load_png(map_params->textures.we);
	while (i != 4)
	{
		if (map_params->textures.texs[i] == NULL)
		{
			map_params->textures.texs[i] = mlx_load_png(side[i]);
			if (map_params->textures.texs[i] == NULL)
				return (EXIT_FAILURE);
			printf("Default texture is used\n");
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int	set_color(t_map_params *map_params, char side, char *str)
{
	int		i;
	char	**colors;
	bool	is_default;

	i = 0;
	colors = ft_split(str, ',');
	if (colors == NULL)
		return (EXIT_FAILURE);
	is_default = false;
	while (colors[i])
		i++;
	if (i != 3)
		return (free_split(colors, i), EXIT_FAILURE);
	else if (side == 'F')
	{
		map_params->floor.color = get_rgba(get_channel(colors[0], &is_default),
				get_channel(colors[1], &is_default),
				get_channel(colors[2], &is_default), 0);
		map_params->floor.is_color = true;
		// printf("floor color is %u\n", map_params->floor.color);
	}
	else if (side == 'C')
	{
		map_params->ceiling.color = get_rgba(
				get_channel(colors[0], &is_default),
				get_channel(colors[1], &is_default),
				get_channel(colors[2], &is_default), 0);
		map_params->ceiling.is_color = true;
		// printf("ceiling color is %u\n", map_params->ceiling.color);
	}
	free_split(colors, i);
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

int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	free_split(char **str, int i)
{
	while (i != 0)
	{
		free(str[i - 1]);
		i--;
	}
	free(str);
}
