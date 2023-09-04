/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekulichk <ekulichk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 18:25:25 by ekulichk          #+#    #+#             */
/*   Updated: 2023/09/04 12:13:27 by ekulichk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/display.h"
#include "include/parser.h"

void	free_texture(t_map *map)
{
	int	i;

	i = 0;
	while (i != N_TEX)
	{
		if (map->tex[i] != NULL)
			mlx_delete_texture(map->tex[i]);
		i++;
	}
}

void	free_map(t_map *map)
{
	int	i;

	i = 0;
	while (i != map->map_height)
	{
		free(map->co[i]);
		i++;
	}
	free(map->co);
	map->co = NULL;
	i = 0;
	while (map->enemy[i] != NULL)
	{
		free(map->enemy[i]);
		i++;
	}
	free(map->ray);
}

void	full_exit(t_map *s)
{
	//free all
	mlx_terminate(s->mlx);
	free_map(s);
	free_texture(s);
	exit(0);
}
