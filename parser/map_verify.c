/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_verify.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekulichk <ekulichk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 14:16:23 by ekulichk          #+#    #+#             */
/*   Updated: 2023/09/01 17:13:09 by ekulichk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../include/parser.h"
#include "../libft/libft.h"

int	map_verify(t_map_set *map_set)
{
	if (map_set->player != 1)
		return (printf("Error: has to be one player\n"), EXIT_FAILURE);
	if (visited_init(map_set))
		return (EXIT_FAILURE);
	if (!dfs(map_set, map_set->player_y, map_set->player_x))
	{
		free(map_set->visited);
		return (printf("Error: map is not closed\n"), EXIT_FAILURE);
	}
	free(map_set->visited);
	return (EXIT_SUCCESS);
}

int	visited_init(t_map_set *map_set)
{
	map_set->visited = malloc(sizeof(bool)
			* map_set->height * map_set->max_width);
	if (map_set->visited == NULL)
		return (print_malloc_failed());
	ft_bzero(
		map_set->visited, sizeof(
			bool) * map_set->height * map_set->max_width);
	return (EXIT_SUCCESS);
}

bool	dfs(t_map_set *map_set, int y, int x)
{
	if (x < 0 || x > map_set->max_width - 1
		|| y < 0 || y > map_set->height - 1)
		return (false);
	if (map_set->map[y][x] == WALL)
		return (true);
	if (is_visited(map_set, y, x))
		return (true);
	set_visited(map_set, y, x);
	return (dfs(map_set, y + 1, x) && dfs(map_set, y, x + 1)
		&& dfs(map_set, y - 1, x) && dfs(map_set, y, x - 1)
		&& dfs(map_set, y + 1, x + 1) && dfs(map_set, y - 1, x - 1)
		&& dfs(map_set, y - 1, x + 1) && dfs(map_set, y + 1, x - 1));
}

bool	is_visited(t_map_set *map_set, int y, int x)
{
	return (map_set->visited[y * map_set->max_width + x]);
}

void	set_visited(t_map_set *map_set, int y, int x)
{
	map_set->visited[y * map_set->max_width + x] = 1;
}
