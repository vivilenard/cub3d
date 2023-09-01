/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekulichk <ekulichk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 17:23:15 by ekulichk          #+#    #+#             */
/*   Updated: 2023/09/01 17:25:12 by ekulichk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../include/parser.h"
#include "../libft/libft.h"

int	create_map(t_map_set *map_set, char *line)
{
	int	len;
	int	cur_width;

	if (extention(map_set))
		return (EXIT_FAILURE);
	cur_width = 0;
	map_set->all_width[map_set->height] = 0;
	len = ft_strlen(line);
	map_set->map[map_set->height] = malloc(sizeof(t_map_char) * len);
	if (map_set->map[map_set->height] == NULL)
		return (print_malloc_failed());
	while (line[cur_width] != '\n' && line[cur_width] != '\0')
	{
		map_set->component = convert_char(
				map_set, line[cur_width], cur_width);
		if (map_set->component == ERROR)
			return (ft_printf("Error: wrong map component\n"), EXIT_FAILURE);
		map_set->map[map_set->height][cur_width] = map_set->component;
		cur_width++;
		map_set->all_width[map_set->height]++;
	}
	if (cur_width > map_set->max_width)
		map_set->max_width = cur_width;
	return (EXIT_SUCCESS);
}

int	extention(t_map_set *map_set)
{
	if (map_set->map_capacity == map_set->height)
	{
		if (map_extend(map_set))
			return (EXIT_FAILURE);
	}
	if (map_set->width_capacity == map_set->height)
	{
		if (all_width_extend(map_set))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	all_width_extend(t_map_set *map_set)
{
	int	*new_array;
	int	new_capacity;
	int	i;

	new_capacity = map_set->width_capacity * 2;
	new_array = malloc(sizeof(int) * new_capacity);
	if (new_array == NULL)
		return (print_malloc_failed());
	i = 0;
	while (i != map_set->height)
	{
		new_array[i] = map_set->all_width[i];
		i++;
	}
	free(map_set->all_width);
	map_set->all_width = new_array;
	map_set->width_capacity = new_capacity;
	return (EXIT_SUCCESS);
}

int	map_extend(t_map_set *map_set)
{
	t_map_char	**new_map;
	int			new_capacity;
	int			i;

	new_capacity = map_set->height * 2;
	new_map = malloc(sizeof(t_map_char *) * new_capacity);
	if (new_map == NULL)
		return (print_malloc_failed());
	i = 0;
	while (i != map_set->height)
	{
		new_map[i] = map_set->map[i];
		i++;
	}
	free(map_set->map);
	map_set->map = new_map;
	map_set->map_capacity = new_capacity;
	return (EXIT_SUCCESS);
}

t_map_char	convert_char(t_map_set *map_set, char c, int width)
{
	if (c == '0' || c == ' ')
		return (SPACE);
	else if (c == '1')
		return (WALL);
	else if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		map_set->player += 1;
		map_set->player_x = width;
		map_set->player_y = map_set->height;
		map_set->player_view = init_player_view(c);
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
