#include "../include/display.h"

t_character	*create_enemy(void)
{
	t_character	*enemy;

	enemy = malloc(sizeof(t_character));
	return (enemy);
}

void	set_enemy_data(t_map *s, int i, int x, int y)
{
		s->enemy[i] = create_enemy();
		s->enemy[i]->index = i;
		s->enemy[i]->lives = ENEMY_LIVES;
		s->enemy[i]->x = (double)x + 0.5;
		s->enemy[i]->y = (double)y + 0.5;
		s->enemy[i]->a = 0;
		s->enemy[i]->dx = s->enemy[i]->x - s->px;
		s->enemy[i]->dy = s->enemy[i]->y - s->py;
		s->enemy[i]->radius = 0.5;
		s->enemy[i]->visible = false;
		s->enemy[i]->in_view = false;
		s->enemy[i]->tex = s->tex[5];
		s->enemy[i]->tex_iter = 0;
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
		set_enemy_data(s, i, x, y);
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
