
// void	free_split(char **str, int i)
// {
// 	while (i != 0)
// 	{
// 		free(str[i - 1]);
// 		i--;
// 	}
// 	free(str);
// }

// t_side	get_side(char *str)
// {
// 	if (ft_strncmp(str, "NO\0", 3) == 0)
// 		return (NORTH);
// 	if (ft_strncmp(str, "SO\0", 3) == 0)
// 		return (SOUTH);
// 	if (ft_strncmp(str, "EA\0", 3) == 0)
// 		return (EAST);
// 	if (ft_strncmp(str, "WE\0", 3) == 0)
// 		return (WEST);
// 	else
// 		return (NONE);
// }

// int	malloc2(size_t count, void **ptr)
// {
// 	*ptr = malloc(count);
// 	return (*ptr == NULL);
// }

// int	print_malloc_failed(void)
// {
// 	printf("Error: malloc failed\n");
// 	return (EXIT_FAILURE);
// }
