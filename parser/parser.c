/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlenard <vlenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 10:26:54 by vlenard           #+#    #+#             */
/*   Updated: 2023/08/05 14:58:41 by vlenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include "../libft/libft.h"

/*
parser needs to give:
- map height and width
- coordinate system co[x][y] or co[y][x]
- textures + floor and ceiling color
*/

int	parser(int argc, char **argv, t_map_params *map_params, int fd)
{
	if (argc != 2)
		return (quick_exit("Error\nexpected a map in format *.cub\n", fd));
	fd = open(argv[1], O_RDONLY);
	if (read(fd, NULL, 0) < 0)
		return (quick_exit("Error\nread() failed\n", fd));
	if (!file_path_check(argv[1]))
		return (quick_exit("Error\nwrong file, expected a map in format *.cub\n", fd));
	if (read_map(map_params, fd))
	{
		// free
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
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
