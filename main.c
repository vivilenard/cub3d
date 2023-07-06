/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlenard <vlenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 12:42:59 by vlenard           #+#    #+#             */
/*   Updated: 2023/07/06 14:46:00 by vlenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	full_exit()
{
	exit(0);
}
t_data	init(t_data *s)
{
	s = malloc(sizeof(t_data));
	s->mlx = mlx_init(WIDTH, HEIGTH, "cub3d", false);
	return (*s);
}

int	map_to_koordinate(t_data *s, char *map)
{
	int	fd;
	s = NULL; //delete
	if (access(map, F_OK == -1) || access(map, R_OK == -1))
		full_exit();
	fd = open(map, O_RDONLY);
		
	return (0);
}

int	parser(t_data *s, int argc, char **argv)
{
	if (argc != 2)
		perror("invalid arguments");
	map_to_koordinate(s, argv[1]);
	return (0);
}

int main(int argc, char **argv)
{
	t_data s;
	s = init(&s);
	parser(&s, argc, argv);
	//raycaster();
	mlx_loop(s.mlx);
	printf("hi\n");
	mlx_terminate(s.mlx);
	return (0);
}