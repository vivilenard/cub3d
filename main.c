
#include "include/cub3d.h"

void	full_exit()
{
	exit(0);
}

int	main(int argc, char **argv)
{
	t_data	s;

	if (parser(argc, argv))
		return (1);
	s = init(&s, argv);	//can go into --> parser
	display(&s);
	return (0);
}
