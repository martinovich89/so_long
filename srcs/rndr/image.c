/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhenry <mhenry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 14:00:36 by mhenry            #+#    #+#             */
/*   Updated: 2021/10/07 00:35:33 by mhenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

int	pick_tex_color(t_env *env, int y, int x)
{
	unsigned int	color;
	char			*src;

	src = env->cur_tex->addr + (
			(int)y * env->cur_tex->line_length) + ((int)x
			* env->cur_tex->bpp / 8);
	color = *(unsigned int *)src;
	if (color == 0x00980088)
		color = 0x00808080;
	return (color);
}

void	put_end_title(t_env *env)
{
	char	*ptr;
	size_t	i;
	size_t	j;

	ptr = env->img.addr + (env->conf->res_h / 2 - 13) * env->img.line_length
		+ (env->conf->res_w / 2 - 75) * 4;
	i = 0;
	while (i < (size_t)env->end.h)
	{
		j = 0;
		while (j < (size_t)env->end.w)
		{
			*(unsigned int *)(ptr + i * env->img.line_length + j
					* env->img.bpp / 8) = *(unsigned int *)(env->end.addr + i
					* env->end.line_length + j * env->end.bpp / 8);
			j++;
		}
		i++;
	}
}

void	draw_image(t_env *env)
{
	size_t			i;
	size_t			j;
	unsigned int	color;

	i = 0;
	while (i < env->conf->res_h - 1)
	{
		j = 0;
		while (j < env->conf->res_w - 1)
		{
			if (j % 50 == 0)
				next_tex(env, i / 50, j / 50);
			if (!env->cur_tex)
				color = 0x00808080;
			else
				color = pick_tex_color(env, i % 50 / 50.0f
						* env->cur_tex->h, j % 50 / 50.0f * env->cur_tex->w);
			if (env->end_level)
				color /= 2;
			*(unsigned int *)(env->img.addr + (i * env->img.line_length
						+ j * (env->img.bpp / 8))) = color;
			j++;
		}
		i++;
	}
}
