#include "../include/cub3d.h"

int	choose_texture(t_ray *r)
{
	int	wall_side;
	
	if (r->door_visible == 1)
		return (DOOR);
	if (r->hit_side == 0) //side x
	{
		if (r->rdx > 0)
			wall_side = WEST;
		else
			wall_side = EAST;
	}
	else
	{
		if (r->rdy < 0)
			wall_side = NORTH;
		else
			wall_side = SOUTH;
	}
	return (wall_side);
}

int	color_tex(t_map *s, t_ray *r, int py)
{
	int				color;
	mlx_texture_t	*tex;
	int				pos;
	double			wall_x;
	int				tex_x;
	int				tex_y;
	double			tex_step;

	tex = s->tex[choose_texture(r)];
	tex_step = 1.0 * tex->height / r->lineheight;
	if (!tex)
		perror ("no tex");
	wall_x = r->hit_x - (int)r->hit_x;
	if ((r->hit_side) == 0)
		wall_x = r->hit_y - (int)r->hit_y;
	tex_x = (int)(wall_x * tex->width);
	tex_y = (py - HEIGTH / 2 + r->lineheight / 2) * tex_step;
	pos = (tex_y * tex->width + tex_x) * tex->bytes_per_pixel;
	color = to_rgbt(tex->pixels[pos + 0], tex->pixels[pos + 1],
		tex->pixels[pos + 2], tex->pixels[pos + 3]);
	return (color);
}

void	take_texture(t_map *s, int p1, int p2, int px)
{
	int	start;
	int	end;

	start = p1;
	end = p2;
	if (p2 < p1)
	{
		start = p2;
		end = p1;
	}
	while (start < end)
	{
		mlx_put_pixel(s->img, px, start, color_tex(s, s->ray, start));
		start++;
	}
}

void	draw_ceiling(t_map *s, int p_end, int px)
{
	int	i;

	i = -1;
	if (p_end <= 0)
		return ;
	while (++i <= p_end)
		mlx_put_pixel(s->img, px, i, s->ceiling);
}

void	draw_floor(t_map *s, int p_start, int px)
{
	if (p_start >= HEIGTH)
		return ;
	while (++p_start < HEIGTH)
		mlx_put_pixel(s->img, px, p_start, s->floor);
}