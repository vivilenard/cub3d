
#include <stdlib.h>
#include "../include/parser.h"
#include "../libft/libft.h"

int	all_width_extend(t_map_params *map_params)
{
	int	*new_array;
	int	new_capacity;
	int	i;

	new_capacity = map_params->width_capacity * 2;
	new_array = malloc(sizeof(int) * new_capacity);
	if (new_array == NULL)
		return (printf("Error: malloc failed\n"), EXIT_FAILURE);
	i = 0;
	while (i != map_params->height)
	{
		new_array[i] = map_params->all_width[i];
		i++;
	}
	free(map_params->all_width);
	map_params->all_width = new_array;
	map_params->width_capacity = new_capacity;
	return (EXIT_SUCCESS);
}

int get_map(t_map_params *map_params, char *line)
{
	int	i;
	int	len;
	int	cur_width;

	if (map_params->capacity == map_params->height)
	{
		if (map_extend(map_params))
			return (EXIT_FAILURE);
	}
	i = 0;
	cur_width = 0;
	if (map_params->width_capacity == map_params->height)
	{
		if (all_width_extend(map_params))
			return (EXIT_FAILURE);
	}
	map_params->all_width[map_params->height] = 0;
	len = ft_strlen(line);
	map_params->map[map_params->height] = malloc(sizeof(t_map_char) * len);
	if (map_params->map[map_params->height] == NULL)
		return (printf("Error: malloc failed\n"), EXIT_FAILURE);
	while (line[cur_width] != '\n' && line[cur_width] != '\0')
	{
		map_params->component = convert_char(
				map_params, line[cur_width], cur_width);
		if (map_params->component == ERROR)
			return (ft_printf("Error: wrong map component\n"), EXIT_FAILURE);
		map_params->map[map_params->height][cur_width] = map_params->component;
		cur_width++;
		map_params->all_width[map_params->height]++;
	}
	if (cur_width > map_params->max_width)
		map_params->max_width = cur_width;
	return (EXIT_SUCCESS);
}

int	map_extend(t_map_params *map_params)
{
	t_map_char	**new_map;
	int			new_capacity;
	int			i;

	new_capacity = map_params->height * 2;
	new_map = malloc(sizeof(t_map_char *) * new_capacity);
	if (new_map == NULL)
		return (printf("Error: malloc failed\n"), EXIT_FAILURE);
	i = 0;
	while (i != map_params->height)
	{
		new_map[i] = map_params->map[i];
		i++;
	}
	free(map_params->map);
	map_params->map = new_map;
	map_params->capacity = new_capacity;
	return (EXIT_SUCCESS);
}

t_map_char	convert_char(t_map_params *map_params, char c, int width)
{
	if (c == '0' || c == ' ')
		return (SPACE);
	else if (c == '1')
		return (WALL);
	else if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		map_params->player += 1;
		map_params->player_x = width;
		map_params->player_y = map_params->height;
		map_params->player_view = init_player_view(c);
		return (PLAYER);
	}
	else if (c == 'H')
		return (CLOSED_DOOR);
	else if (c == 'I')
		return (OPENED_DOOR);
	else if (c == 'X')
		return (ENEMY);
	else
		return (ERROR);
}
