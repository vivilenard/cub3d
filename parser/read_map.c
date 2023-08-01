/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekulichk <ekulichk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 11:52:17 by ekulichk          #+#    #+#             */
/*   Updated: 2023/08/01 13:31:51 by ekulichk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"
#include <stdlib.h>
#include <unistd.h>

int	read_map(t_map_params *map_params, int fd)
{
	int				width_temp;
	int				read_bytes;
	char			c;

	width_temp = 0;
	if (map_init(map_params))
		return (EXIT_FAILURE);
	read_bytes = 1;
	while (read_bytes == 1)
	{
		read_bytes = read(fd, &c, 1);
		if (read_bytes_check(map_params, &read_bytes, &width_temp, c))
			return (EXIT_FAILURE);
	}
	// if (!map_verify(map_params))
	// 	return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	read_bytes_check(
	t_map_params *map_params, int *read_bytes, int *width_temp, char c)
{
	if (*read_bytes == -1)
		return (printf("Error\nread() failed\n"), EXIT_FAILURE);
	// if (map_fill_in(map_params, c, read_bytes, width_temp))
	// 	return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
