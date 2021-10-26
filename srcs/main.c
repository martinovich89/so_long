/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhenry <mhenry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 00:07:02 by martin            #+#    #+#             */
/*   Updated: 2021/10/26 14:37:07 by mhenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

int	render_next_frame(t_env *env)
{
	update_hero_pos(env);
	draw_image(env);
	if (env->end_level)
		put_end_title(env);
	mlx_put_image_to_window(env->mlx, env->win, env->img.img, 0, 0);
	return (0);
}

void	launch_game(t_env *env)
{
	parse_map(env);
	if (check_map(env))
		ft_error("Wrong map\n", env);
	set_conf(env);
	my_mlx_init(env);
	mlx_hook(env->win, 2, 1L << 0, key_press, env);
	mlx_hook(env->win, 3, 1L << 1, key_release, env);
	mlx_hook(env->win, 17, 1L << 17, close_window, env);
	mlx_loop_hook(env->mlx, render_next_frame, env);
	mlx_loop(env->mlx);
}

int	main(int argc, char **argv)
{
	t_env	*env;

	if (set_to_zero(sizeof(t_env), &env) != 0)
		ft_error("failed to allocate env\n", env);
	check_args(argc, env);
	check_fd(argv, env);
	if (set_to_zero(sizeof(t_conf), &env->conf) != 0)
		ft_error("failed to allocate env\n", env);
	env->conf->file = ft_strdup(argv[1]);
	if (!env->conf->file)
		ft_error("failed to allocate conf.file\n", env);
	launch_game(env);
	ft_clear_env(env);
	exit(0);
	return (0);
}
