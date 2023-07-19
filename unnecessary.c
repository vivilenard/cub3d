void	simple_steps(t_data *s, double step)
{
	if (mlx_is_key_down(s->mlx, MLX_KEY_W))
	{
		if (s->py - (step + s->p_radius) >= 0 && s->co[(int)s->px][(int)(s->py - step)] != '1')
			s->py -= (step);
	}
	if (mlx_is_key_down(s->mlx, MLX_KEY_A))
	{
		if (s->px - (step + s->p_radius) >= 0 && s->co[(int)(s->px - step)][(int)(s->py)] != '1')
			s->px -= step;
	}
	if (mlx_is_key_down(s->mlx, MLX_KEY_S))
	{
		if (s->py + (step + s->p_radius) < s->map_height && s->co[(int)s->px][(int)(s->py + step)] != '1')
			s->py += step;
	}
	if (mlx_is_key_down(s->mlx, MLX_KEY_D))
	{
		if (s->px + (step + s->p_radius) < s->map_width && s->co[(int)(s->px + step)][(int)(s->py)] != '1')
			s->px += step;
	}	
}