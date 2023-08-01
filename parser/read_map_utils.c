/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekulichk <ekulichk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 11:55:38 by ekulichk          #+#    #+#             */
/*   Updated: 2023/08/01 16:19:49 by ekulichk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"
#include <stdlib.h>

int	map_init(t_map_params *map_params)
{
	map_params->map_capacity = 1;
	map_params->map = malloc(
			sizeof(t_map_component *) * map_params->map_capacity);
	if (map_params->map == NULL)
		return (printf("Error\nmalloc failed\n"), EXIT_FAILURE);
	map_params->count = 0;
	map_params->orintation.no = NULL;
	map_params->orintation.so = NULL;
	map_params->orintation.we = NULL;
	map_params->orintation.ea = NULL;
	map_params->width = 0;
	map_params->height = 0;
	map_params->player = 0;
	map_params->doors = 0;
	map_params->identifier = 0;
	return (EXIT_SUCCESS);
}
