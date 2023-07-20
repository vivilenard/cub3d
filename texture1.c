
int	get_tex_color(mlx_texture_t *tex, int pos)
{
	int pos_tex;

	pos_tex = pos * tex->bytes_per_pixel;
	return(to_rgbt(tex->pixels[0], tex->pixels[1], tex->pixels[2], tex->pixels[3]));
	
}

void	print_tex(t_data *s, int start, int end, int px)
{
	int		tex_height;
	//double	tex_y;
	tex_height = s->tex[s->wall_tex]->height - 1;
	s->tex_step = 1.0 * tex_height / s->lineheight;
	s->tex_y = (start - HEIGTH / 2 + s->lineheight / 2) * s->tex_step ; //this is right
	//s->tex_y = s->lineheight / 2 - (HEIGTH / 2 - start);
	//s->tex_y = 1;
	while (start < end)
	{
		mlx_put_pixel(s->img, px, start, get_tex_color(s->tex[s->wall_tex], (int)(tex_height * s->tex_y) + s->tex_x));//s->tex[wall_side][tex_height * (int)s->tex_pos + tex_x]);
		s->tex_y += s->tex_step;
		start++;
	}
}

void	get_texture(t_data *s, int p1, int p2, int px)
{
	int	start = p1;
	int	end = p2;
	int	tex_height;
	double	wall_x;

	tex_height = s->tex[s->wall_tex]->height;
	if (p2 < p1)
	{
		start = p2;
		end = p1;
	}
	s->wall_tex = choose_texture(s);
	wall_x = s->hit_x - (int)s->hit_x;
	if ((s->hit_side) == 0)
		wall_x = s->hit_y - (int)s->hit_y;
	s->tex_x = (int)(wall_x * s->tex[s->wall_tex]->width);
	print_tex(s, start, end, px);
}
