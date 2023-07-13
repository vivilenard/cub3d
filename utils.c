/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlenard <vlenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 18:38:49 by vlenard           #+#    #+#             */
/*   Updated: 2023/07/13 14:19:39 by vlenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	mapheight(char *map)
{
	char	*line;
	int		i;
	int		fd;

	i = 0;
	fd = open(map, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		i++;
		line = get_next_line(fd);
	}
	close(fd);
	return (i);
}

int	mapwidth(char *map)
{
	char	*line;
	size_t		len;
	int		fd;

	len = 0;
	fd = open(map, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		if (len < ft_strlen(line))
			len = ft_strlen(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (len - 1);
}

int	scan_coordinates(t_data *s, int (*f)(t_data *s, int x, int y))
{
	int	x;
	int	y;
	
	x = 0;
	y = 0;
	while (s->co[x])
	{
		while (s->co[x][y])
		{
			if (f(s, x, y))
				return (1);
			y++;
		}
		y = 0;
		x++;
	}
	return (0);
}

void	print_coordinates(t_data s)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (s.co[x][y])
	{
	//	printf("y: %d\n", y);
		while (s.co[x][y])
		{
			printf("%c ", s.co[x][y]);
			x++;
		}
		x = 0;
		printf("\n");
		y++;
	}
}