
#include "include/cub3d.h"
#include "include/parser.h"

void segfault_sigaction(int signal, siginfo_t *si, void *arg) {
    void *error_addr = si->si_addr;
    void *array[10];
    size_t size;
    (void)signal;
    (void)arg;
    // get void*'s for all entries on the stack
    size = backtrace(array, 10);
    fprintf(stderr, "Error at address: 0x%lx\n", (long)error_addr);
    // print out all the frames to stderr
    backtrace_symbols_fd(array, size, STDERR_FILENO);
    exit(1);
}

void	full_exit(t_map *s)
{
	// int i = 0;
	// while (s->tex[i])
	// {
	// 	mlx_delete_texture(s->tex[i]);
	// 	i++;
	// }
	// system ("leaks cub3D");
	s = NULL; //dangerous!
	//mlx_terminate(s->mlx);
	exit(0);
}

int	main(int argc, char **argv)
{
	int				fd;
	t_map			s;
	t_map_params	map_params;

// struct sigaction sa;
//     sa.sa_flags = SA_SIGINFO;
//     sa.sa_sigaction = segfault_sigaction;
//     sigemptyset(&sa.sa_mask);
//     sigaction(SIGSEGV, &sa, NULL);

	if (argc < 2)
		return (printf("Error\nexpected a map in format *.cub\n"), EXIT_FAILURE);
	fd = open(argv[1], O_RDONLY);
	if (read(fd, NULL, 0) < 0)
		return (quick_exit("Error\nread() failed\n", fd));
	s.mlx = mlx_init(WIDTH, HEIGTH, "cub3d", false);
	if (!s.mlx)
		return (perror("no mlx"), EXIT_FAILURE);
	// s.mlx = mlx_init(WIDTH, HEIGTH, "cub3d", false);
	// if (!s.mlx)
	// 	printf("no mlx");
	if (parser(&map_params, &s, argv, fd))
		return (close(fd), EXIT_FAILURE);
	print_map(&s);
	display(&s);
	full_exit(&s);
	return (EXIT_SUCCESS);
}
