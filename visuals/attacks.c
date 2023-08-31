#include "../include/display.h"

int	attack_player(t_map *s, t_character *e)
{
	if (!e->lives)
		return (1);
	if (e->visible && e->dist < 0.8 && s->lives > 0)
		s->lives--;
	return (1);
}

int	get_shot(t_map *s)
{
	int		lives_tmp;
	float	mv;

	mv = 0.05;
	lives_tmp = s->lives;
	if (s->frame->counter % 70 == 0)
		loop_enemies(s, attack_player);
	if (lives_tmp <= s->lives && !s->frame->n_backstep)
		return (0);
	if (lives_tmp > s->lives)
	{
		system("afplay sounds/Kick.wav&");
		color_full_screen(s->img, 0xFF0000FF);
		s->frame->n_backstep = 10;
		return (1);
	}
	if (!collide(s->co, (int)(s->px - mv * s->pdx), (int)s->py))
		s->px -= mv * s->pdx;
	if (!collide(s->co, (int)(s->px), (int)(s->py - s->pdy * mv)))
		s->py -= mv * s->pdy;
	if (s->frame->n_backstep)
		s->frame->n_backstep--;
	return (0);
}

int	die(t_map *s)
{
	if (s->lives > 0)
		return (0);
	mlx_delete_image(s->mlx, s->minimap);
	color_full_screen(s->img, 0x00000000);
	return (1);
}

void	shoot_enemy(t_map *s, t_character *e)
{
	float	shift_x;
	float	shift_y;

	if (e->lives <= 0)
		return ;
	e->lives--;
	shift_x = e->x - e->dx / sqrtf((e->dx * e->dx + e->dy * e->dy)) * 0.2;
	shift_y = e->y - e->dy / sqrtf((e->dx * e->dx + e->dy * e->dy)) * 0.2;
	if (s->co[(int)shift_y][(int)shift_x] != WALL
		&& s->co[(int)shift_y][(int)shift_x] != CLOSED_DOOR)
	{
		e->x = shift_x;
		e->y = shift_y;
	}
}
