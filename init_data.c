/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlenard <vlenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 17:53:23 by vlenard           #+#    #+#             */
/*   Updated: 2023/07/12 18:52:16 by vlenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_data	init(t_data *s, char **argv)
{
	s = malloc(sizeof(t_data));
	s->mlx = mlx_init(WIDTH, HEIGTH, "cub3d", false);
	map_to_koordinate(s, argv[1]);
	return (*s);
}

int	assign_line(char *line, t_data *s, int	y)
{
	int	x;
	x = 0;

	//printf("%d/%d	\n", x, y);
	while (line[x] && line[x] != '\n')
	{
		s->co[x][y] = line[x];
		//printf("%d/%d: %c ", x, y, s->co[x][y]);
		x++;
	}
	//printf("\n");
	return (1);
}

int	allocate_map(t_data *s)
{
	int	x;

	x = 0;
	s->co = malloc((s->map_width + 1) * sizeof(char *));
	if (!s->co)
		return (perror("malloc"), 0);
	s->co[s->map_width] = NULL;
	while (x <= s->map_width)
	{
		s->co[x] = ft_calloc(s->map_height + 1, 1);
		if (!s->co[x])
			return (perror("malloc"), 0);
		x++;
	}
	s->co[x] = NULL;
	//printf("allocated %d lines\n", x);
	return (1);
}