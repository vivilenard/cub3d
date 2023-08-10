/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekulichk <ekulichk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 11:55:38 by ekulichk          #+#    #+#             */
/*   Updated: 2023/08/10 23:31:31 by ekulichk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../include/parser.h"
#include "../libft/libft.h"

int get_map(t_map_params *map_params, char *line)
{
	int	len;

	len = ft_strlen(line);
	map_params->map[map_params->height] = malloc(sizeof(t_map_char) * len);
	if (map_params->map[map_params->height] == NULL)
	{
		// free
		return (printf("Error: malloc failed\n"), EXIT_FAILURE);
	}
	while (line[map_params->cur_width] != '\n' && line[map_params->cur_width] != '\0')
	{
		map_params->component = convert_char(map_params, line[map_params->cur_width]);
		if (map_params->component == ERROR)
		{
			ft_printf("Error: wrong map component\n");
			return (EXIT_FAILURE);
		}
		map_params->map[map_params->height][map_params->cur_width] = map_params->component;
		map_params->cur_width++;
		map_params->all_width[map_params->height]++;;
	}
	if (map_params->cur_width > map_params->max_width)
		map_params->max_width = map_params->cur_width;
	return (EXIT_SUCCESS);
}

t_map_char	convert_char(t_map_params *map_params, char c)
{
	if (c == '0' || c == ' ')
		return (SPACE);
	else if (c == '1')
		return (WALL);
	else if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		map_params->player += 1;
		map_params->player_x = map_params->cur_width;
		map_params->player_y = map_params->height;
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
