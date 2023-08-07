
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

int	parser(t_map *map, t_map_params *map_params, char **argv, int fd)
{
	if (!file_path_check(argv[1]))
		return (quick_exit("Error: wrong file, expected a map in format *.cub\n", fd));
	if (read_map(map, map_params, fd))
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
