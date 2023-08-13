
#include "../include/parser.h"
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include "../libft/libft.h"

int	parser(t_map *map, t_map_params *map_params, char **argv, int fd)
{
	if (!file_path_check(argv[1]))
		return (quick_exit("Error: wrong file, expected a map in format *.cub\n", fd));
	if (read_map(map, map_params, fd))
	{
		// free
		return (EXIT_FAILURE);
	}
	map->co_map = map_params->map;
	map_params->map = NULL;
	map->px = (double) map_params->player_x + 0.5;
	map->py = (double) map_params->player_y + 0.5;
	// map->pa = init_player_view(map_params)
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

int	malloc2(size_t count, void **ptr)
{
	*ptr = malloc(count);
	return (*ptr == NULL);
}

int	print_malloc_failed(void)
{
	printf("Error: malloc failed\n");
	return (EXIT_FAILURE);
}
