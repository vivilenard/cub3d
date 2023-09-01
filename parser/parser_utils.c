
#include <stdio.h>
#include "../include/parser.h"

int	print_malloc_failed(void)
{
	return (printf("Error: malloc failed\n"), EXIT_FAILURE);
}
