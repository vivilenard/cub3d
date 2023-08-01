
#include "include/cub3d.h"

void	full_exit()
{
	//system ("leaks cub3D");
	exit(0);
}

int	main(int argc, char **argv)
{
	int				fd;
	t_map			s;
	t_map_params	map_params;

	if (parser(argc, argv, &map_params, fd))
		return (EXIT_FAILURE);
	s = init(&s, argv);
	display(&s);

	return (EXIT_SUCCESS);
}
