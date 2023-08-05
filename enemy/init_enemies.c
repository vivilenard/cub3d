#include "../include/cub3d.h"

t_character	*create_enemy(t_map *s, int n)
{
	t_character *enemy;

	enemy = malloc(sizeof(t_character));
	return (enemy);
}

int	position_enemy(t_map *s, int x, int y)
{
	int	i;

	i = 0;
	if (s->co[x][y] != 'e')
		return (0);
	while (s->enemy[i] != NULL)
		i++;
	if (i >= N_ENEMIES)
		return (0);
	else
	{
		s->enemy[i] = create_enemy(s, i);
		s->enemy[i]->x = (double)x + 0.5;
		s->enemy[i]->y = (double)y + 0.5;
		s->enemy[i]->a = 0;
		s->enemy[i]->dx = s->enemy[i]->y - s->px;
		s->enemy[i]->dy = s->enemy[i]->y - s->py;
		s->enemy[i]->radius = 0.03;
	}
	return (0);
}

void	get_enemies(t_map *s)
{
	int	i;

	i = -1;
	while (++i < N_ENEMIES)
		s->enemy[i] = NULL;
	scan_coordinates(s, position_enemy);
}