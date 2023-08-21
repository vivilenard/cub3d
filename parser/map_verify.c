/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_verify.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekulichk <ekulichk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 14:16:23 by ekulichk          #+#    #+#             */
/*   Updated: 2023/08/21 16:38:10 by ekulichk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../include/parser.h"
#include "../libft/libft.h"

int	map_verify(t_map_params *map_params)
{
	int	y;
	int	x;

	y = 0;
	x = 0;
	if (map_params->player != 1)
		return (printf("Error: has to be one player\n"), EXIT_FAILURE);
	if (visited_init(map_params))
		return (EXIT_FAILURE);
	if (!dfs(map_params, map_params->player_y, map_params->player_x))
		return (printf("Error: map is not closed\n"), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	visited_init(t_map_params *map_params)
{
	map_params->visited = malloc(sizeof(bool)
			* map_params->height * map_params->max_width);
	if (map_params->visited == NULL)
	{
		// free_map(map_params);
		// free_visited(map_params);
		return (printf("Error: malloc() failed\n"), EXIT_FAILURE);
	}
	ft_bzero(
		map_params->visited, sizeof(
			bool) * map_params->height * map_params->max_width);
	return (EXIT_SUCCESS);
}

bool	dfs(t_map_params *map_params, int y, int x)
{
	if (x < 0 || x > map_params->max_width - 1
		|| y < 0 || y > map_params->height - 1)
		return (false);
	if (map_params->map[y][x] == WALL)
		return (true);
		// return (error, message);
	if (is_visited(map_params, y, x))
		return (true);
	set_visited(map_params, y, x);
	return (dfs(map_params, y + 1, x) && dfs(map_params, y, x + 1)
		&& dfs(map_params, y - 1, x) && dfs(map_params, y, x - 1)
		&& dfs(map_params, y + 1, x + 1) && dfs(map_params, y - 1, x - 1)
		&& dfs(map_params, y - 1, x + 1) && dfs(map_params, y + 1, x - 1));
}

bool	is_visited(t_map_params *map_params, int y, int x)
{
	return (map_params->visited[y * map_params->max_width + x]);
}

void	set_visited(t_map_params *map_params, int y, int x)
{
	map_params->visited[y * map_params->max_width + x] = 1;
}
