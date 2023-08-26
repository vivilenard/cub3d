#include "../include/cub3d.h"

int	attack_player(t_map *s, t_character *e)
{
	if (e->dist < 0.8 && s->lives > 0)
		s->lives--;
	return (1);
}

int	get_shot(t_map *s)
{
	int	lives_tmp;

	lives_tmp = s->lives;
	if (s->frame % 50 != 0)
		return (0);
	loop_enemies(s, attack_player);
	if (lives_tmp > s->lives)
		return (color_full_screen(s->img, 0xFF0000FF), 1);
	return (0);
}

int die(t_map *s)
{
	if (s->lives > 0)
		return (0);
	mlx_delete_image(s->mlx, s->minimap);
	color_full_screen(s->img, 0x00000000);
	return (1);
}
