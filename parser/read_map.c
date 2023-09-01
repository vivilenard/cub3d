/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekulichk <ekulichk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 11:52:17 by ekulichk          #+#    #+#             */
/*   Updated: 2023/09/01 17:17:29 by ekulichk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include "../include/parser.h"
#include "../libft/libft.h"
#include "../MLX42/include/MLX42/MLX42.h"

int	read_map(t_map_set *map_set, int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line != NULL)
	{
		if (*line == '\n')
		{
			if (map_set->map_start && !map_set->map_end)
				map_set->map_end = true;
		}
		else
		{
			if (proceed_line(map_set, line))
				return (free(line), EXIT_FAILURE);
		}
		if (*line != '\n' && map_set->map_end)
			return (free(line), printf("Error: empty line in a map content\n"),
				EXIT_FAILURE);
		free(line);
		line = get_next_line(fd);
	}
	return (EXIT_SUCCESS);
}

int	proceed_line(t_map_set *map_set, char *line)
{
	if (map_set->identifier != 6)
	{
		if (get_identifier(map_set, line))
			return (EXIT_FAILURE);
	}
	else
	{
		if (create_map(map_set, line))
			return (EXIT_FAILURE);
		map_set->map_start = true;
		map_set->height++;
	}
	return (EXIT_SUCCESS);
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
