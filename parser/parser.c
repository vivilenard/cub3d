/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlenard <vlenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 10:26:54 by vlenard           #+#    #+#             */
/*   Updated: 2023/07/31 13:17:11 by vlenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include "../libft/libft.h"
//#include "../cub3d.h"

static int	file_path_check(char *argv)
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
			return (0);
		i++;
	}
	return (1);
}

int	parser(int argc, char **argv)
{
	int	fd;

	if (argc != 2)
		return (printf("Error\nexpected a map in format *.cub\n"), 1);
	fd = open(argv[1], O_RDONLY);
	if (read(fd, NULL, 0) < 0)
	{
		close(fd);
		return (perror("Error\nread() failed"), 1);
	}
	else if (!file_path_check(argv[1]))
	{
		close(fd);
		return (printf("Error\nwrong file, expected a map in format *.cub\n"), 1);
	}
	// else
	// 	read_map();
	return (0);
}
