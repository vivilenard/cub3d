#include "../include/cub3d.h"

double	delta_dist(double side)
{
	return (fabs(1 / side));
}

int	calculate_lineheight(double distance)
{
	return ((int)((HEIGTH / distance) * (90 / VIEW_ANGLE)));
}

color	to_rgbt(int r, int g, int b, int t)
{
	return ((r << 24) + (g << 16) + (b << 8) + t);
}
