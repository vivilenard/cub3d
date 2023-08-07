/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekulichk <ekulichk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 11:52:17 by ekulichk          #+#    #+#             */
/*   Updated: 2023/08/06 15:08:28 by ekulichk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include "../include/parser.h"
#include "../libft/libft.h"
#include "../MLX42/include/MLX42/MLX42.h"

int get_map(t_map_params *map_params, char *str)
{
	return (EXIT_SUCCESS);
}

int	read_map(t_map *map, t_map_params *map_params, int fd)
{
	int		line_y;
	char	*line;

	if (map_params_init(map_params))
		return (EXIT_FAILURE);
	line_y = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (*line == '\n')
		{
			line = get_next_line(fd);
			continue;
		}
		 if (map_params->identifier != 6)
		{
			if (get_identifier(map, map_params, line))
				return (EXIT_FAILURE);
		}
		else
		{
			get_map(map_params, line);
		}
		line = get_next_line(fd);
	}
	// }
	// if (map_verify(map_params))
	// {
	// 	// free
	// 	return (EXIT_FAILURE);
	// }
	// free line ?
	return (EXIT_SUCCESS);
}

// int	map_verify(t_map_params *map_params)
// {
// 	if (map_params->player != 1)
// 	{
// 		// free
// 		return (printf("Error\nhas to be one player\n"), EXIT_FAILURE);
// 	}
// 	return (EXIT_SUCCESS);
// 	// if map is closed
// }
