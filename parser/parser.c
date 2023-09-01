/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekulichk <ekulichk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 16:58:58 by ekulichk          #+#    #+#             */
/*   Updated: 2023/09/01 18:27:10 by ekulichk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"
#include "../include/cub3d.h"
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <math.h>
#include "../libft/libft.h"

int	parser(t_map_set *map_set, t_map *map, char **argv, int fd)
{
	if (!file_path_check(argv[1]))
		return (quick_exit(
				"Error: wrong file, expected a map in format *.cub\n", fd));
	if (map_set_init(map_set))
		return (EXIT_FAILURE);
	if (read_map(map_set, fd))
		return (free_if_error(map_set));
	if (set_textures(map_set, map))
		return (free_if_error(map_set), free_texture(map), EXIT_FAILURE);
	if (map_set->map[0] == NULL)
		return (printf("Error: map is empty\n"), free_if_error(map_set));
	if (zero_extend(map_set))
		return (free_if_error(map_set));
	if (map_verify(map_set))
		return (free_if_error(map_set));
	fill_in_t_map(map_set, map);
	free(map_set->all_width);
	return (EXIT_SUCCESS);
}

void	fill_in_t_map(t_map_set *map_set, t_map *map)
{
	map->co = map_set->map;
	map_set->map = NULL;
	map->map_height = map_set->height;
	map->map_width = map_set->max_width;
	map->px = (double) map_set->player_x + 0.5;
	map->py = (double) map_set->player_y + 0.5;
	map->pa = map_set->player_view;
	map->pdx = cos(map->pa);
	map->pdy = sin(map->pa);
	map->p_radius = 0.09;
	map->mouse_pos = 0;
	map->floor = map_set->floor.color;
	map->ceiling = map_set->ceiling.color;
	map->co[map_set->player_y][map_set->player_x] = SPACE;
	map->lives = LIVES;
}

int	file_path_check(char *argv)
{
	int		i;
	int		len;
	char	*cub;

	i = 0;
	cub = ".cub";
	len = ft_strlen(argv) - 4;
	while (i != 5)
	{
		if (argv[len + i] != cub[i])
			return (EXIT_SUCCESS);
		i++;
	}
	return (EXIT_FAILURE);
}

int	quick_exit(char *str, int fd)
{
	printf("%s", str);
	close(fd);
	return (EXIT_FAILURE);
}
