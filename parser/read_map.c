/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekulichk <ekulichk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 11:52:17 by ekulichk          #+#    #+#             */
/*   Updated: 2023/08/01 17:51:27 by ekulichk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"
#include <stdlib.h>
#include <unistd.h>

// int	fill_in_identifier(t_map_params *map_params, char c)
// {
// 	;
// }

int	read_map(t_map_params *map_params, int fd)
{
	int				width_temp;
	int				read_bytes;
	char			c;

	width_temp = 0;
	if (map_init(map_params))
		return (EXIT_FAILURE);
	read_bytes = 1;
	// while (read_bytes == 1)
	// {
	// 	read_bytes = read(fd, &c, 1);
	// 	if (read_bytes == -1)
	// 	{
	// 		// free
	// 		return (printf("Error\nread() failed\n"), EXIT_FAILURE);
	// 	}
		// if (map_params->identifier <= 6)
		// {
		// 	fill_in_identifier(map_params, c);
		// }
		// else
		// {
		// 	fill_in_map();
		// }
	// }
	// if (map_verify(map_params))
	// {
	// 	// free
	// 	return (EXIT_FAILURE);
	// }
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
