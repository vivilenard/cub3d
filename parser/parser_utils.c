/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekulichk <ekulichk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 16:58:43 by ekulichk          #+#    #+#             */
/*   Updated: 2023/09/01 17:50:36 by ekulichk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../include/parser.h"

void	free_split(char **str, int i)
{
	while (i != 0)
	{
		free(str[i - 1]);
		i--;
	}
	free(str);
}

void	free_map_set(t_map_set *map_set)
{
	int	i;

	i = 0;
	while (i != map_set->height + 1)
	{
		free(map_set->map[i]);
		i++;
	}
	free(map_set->map);
	free(map_set->all_width);
}

void	free_sides(t_map_set *map_set)
{
	if (map_set->textures.no != NULL)
		free(map_set->textures.no);
	if (map_set->textures.so != NULL)
		free(map_set->textures.so);
	if (map_set->textures.we != NULL)
		free(map_set->textures.we);
	if (map_set->textures.ea != NULL)
		free(map_set->textures.ea);
}

int	free_if_error(t_map_set *map_set)
{
	free_sides(map_set);
	free_map_set(map_set);
	return (EXIT_FAILURE);
}

int	print_malloc_failed(void)
{
	return (printf("Error: malloc failed\n"), EXIT_FAILURE);
}
