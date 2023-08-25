#include "../include/cub3d.h"

t_character	*create_enemy()
{
	t_character *enemy;

	enemy = malloc(sizeof(t_character));
	return (enemy);
}

int	position_enemy(t_map *s, int x, int y)
{
	int	i;

	i = 0;
	if (s->co[y][x] != ENEMY)
		return (0);
	while (s->enemy[i] != NULL)
		i++;
	if (i >= MAX_ENEMIES)
		return (0);
	else
	{
		s->enemy[i] = create_enemy();
		s->enemy[i]->index = i;
		s->enemy[i]->lives = ENEMY_LIVES;
		s->enemy[i]->x = (double)x + 0.5;
		s->enemy[i]->y = (double)y + 0.5;
		s->enemy[i]->a = 0;
		s->enemy[i]->dx = s->enemy[i]->x - s->px;  //changed s->enemy[i]->y
		s->enemy[i]->dy = s->enemy[i]->y - s->py;
		s->enemy[i]->radius = 0.5;
		s->enemy[i]->visible = false;
		s->enemy[i]->in_view = false;
		s->enemy[i]->tex = s->tex[5];
	}
	return (0);
}

void	get_enemies(t_map *s)
{
	int	i;

	i = -1;
	while (++i <= MAX_ENEMIES)
		s->enemy[i] = NULL;
	scan_coordinates(s, position_enemy);
}

int	enemy_invisible(t_character *e)
{
	e->visible = false;
	e->in_view = false;
	e->pix_start = -1;
	e->pix_end = -1;
	return (1);
}

int	number_enemies(t_map *s) //dont need
{
	int	i;

	i = 0;
	while (s->enemy[i])
		i++;
	return (i);
}

int	highest_dist_enemy(t_map *s, double *dist)
{
	int		i = -1;
	double	highest_dist = -1;
	int		index = -1;

	while (s->enemy[++i])
	{
		if (highest_dist < dist[i])
		{
			highest_dist = dist[i];
			index = i;
		}
	}
	return (index);
}