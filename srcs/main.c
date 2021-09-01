/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 00:07:02 by martin            #+#    #+#             */
/*   Updated: 2020/10/17 00:07:03 by martin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int		map_too_small(char **map)
{
	size_t i;
	size_t j;

	i = 0;
	j = 0;
	while (map[i][j])
	{
		j = 0;
		while (map[i][j])
			j++;
		if (j < 3)
			return(1);
		i++;
	}
	return (i < 3);
}

int		map_not_rectangular(char **map)
{
	size_t i;
	size_t j;
	size_t width;

	i = 0;
	j = 0;
	while (map[i][j])
		j++;
	width = j;
	j = 0;
	while (map[i][j])
	{
		j = 0;
		while (map[i][j])
			j++;
		if (j != width)
			return (1);
		i++;
	}
	return (0);
}

int		wrong_character(char **map)
{
	size_t i;
	size_t j;

	i = 0;
	j = 0;
	while (map[i][j])
	{
		j = 0;
		while (map[i][j])
		{
			if (!is_charset(map[i][j], "01CEP"))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int		not_well_circled(char **map)
{
	size_t i;
	size_t j;
	size_t height;

	i = 0;
	j = 0;
	while (map[i])
		i++;
	height = i;
	i = 0;
	while (map[i] + j)
	{
		if (map[i][j] != "1")
			return (1);
		j++;
	}
	while (i < height - 1)
	{
		if (map[i][0] != "1" || map[i][j - 1] != "1")
			return (1);
		i++;
	}
	return (0);
}

int		check_map(char **map)
{
	if (map_too_small(map))
		return (1);
	if (map_not_rectangular(map))
		return (2);
	if (wrong_character(map))
		return (3);
	if (not_well_circled(map))
		return (4);
	return (0);
}

void	move_hero_pos(int dir)
{
	if (dir == 1)
	{
		map->hero_pos[0]--;
		map->move_count++;
	}
	if (dir == 2)
	{
		map->hero_pos[0]++;
		map->move_count++;
	}
	if (dir == 3)
	{
		map->hero_pos[1]--;
		map->move_count++;
	}
	if (dir == 4)
	{
		map->hero_pos[1]++;
		map->move_count++;
	}
}

void	handle_hero_move(t_map *map, int dir)
{
	map->map[map->hero_pos[1]][map->hero_pos[0]] == "0";
	move_hero_pos(map, dir);
	if (map->map[map->hero_pos[1]][map->hero_pos[0]] == "C")
	{
		map->map[map->hero_pos[1]][map->hero_pos[0]] == "0";
		map->collectibles++;
	}
}

void	update_hero_pos(t_env *env, t_map *map)
{
	if (env->left == 1 && map->hero_pos[0] > 0 &&
	map->map[map->hero_pos[1]][map->hero_pos[0] - 1] != "1")
	{
		handle_hero_move(map, 1);
		env->left = 0;
	}
	if (env->right == 1 && map->hero_pos[0] + 1 < map->width &&
	map->map[map->hero_pos[1]][map->hero_pos[0] + 1] != "1")
	{
		handle_hero_move(map, 2);
		env->right = 0;
	}
	if (env->down == 1 && map->hero_pos[1] + 1 < map->height &&
	map->map[map->hero_pos[1] + 1][map->hero_pos[0]] != "1")
	{
		handle_hero_move(map, 3);
		env->down = 0;
	}
	if (env->up == 1 && map->hero_pos[1] > 0 &&
	map->map[map->hero_pos[1]][map->hero_pos[0] - 1] != "1")
	{
		handle_hero_move(map, 4);
		env->up = 0;
	}
}

void			draw_image(t_env *env, t_data *data, unsigned int **tab)
{
	int x;
	int y;

	draw_background(tab);
	draw_walls(tab);
	draw_hero(tab);
	draw_items(tab);
	y = 0;
	while (y < env->conf->res_h)
	{
		x = 0;
		while (x < env->conf->res_w)
		{
			my_mlx_pixel_put(data, x, y, tab[y][x]);
			x++;
		}
		y++;
	}
}

int		render_next_frame(t_env *env)
{
	reset_sheet(env);
	update_hero_pos(env, env->map);
	//guards_pos(env);
	draw_image(env, &env->img, env->rndr->sheet);
	mlx_put_image_to_window(env->mlx, env->win, env->img.img, 0, 0);
	return (0);
}

void	launch_game(t_env *env)
{
	parse_params(env);
	parse_map(env);
	init_player(env);
	init_mlx(env);
	mlx_hook(env->win, 2, 1L << 0, key_press, env);
	mlx_hook(env->win, 3, 1L << 1, key_release, env);
	mlx_hook(env->win, 17, 1L << 17, close_window, env);
	mlx_loop_hook(env->mlx, render_next_frame, env);
	mlx_loop(env->mlx);
}

void	check_arg(t_env *env, int argc, char **argv)
{
	if (argc < 1)
		ft_error("No argument\n", env);
	else if (argc > 0 && argc < 2)
		ft_error("Empty argument\n", env);
	else if (argc > 3)
		ft_error("Too many arguments\n", env);
	else if (argc == 3 && ft_strcmp(argv[2], "--save") != 0)
		ft_error("Incorrect argument for save image\n", env);
	else if (argc == 3)
		env->conf->is_bmp = 1;
	else
		env->conf->is_bmp = 0;
}

void	check_args(t_env env)
{
	if (argc != 2)
		ft_error("Error: Program must be launched with 2 arguments\n", env);
	return (0);
}

void	check_fd(char **argv, t_env *env)
{
	char	*line;
	int		fd;
	int		ret;
	char	buffer[1];

	line = NULL;
	fd = 0;
	fd = open(argv[1], O_RDONLY);
	if (fd < 0 || (ret = read(fd, buffer, 1)) < 0)
		ft_error("The file does not exist\n", env);
	if ((line = (ft_strrchr(argv[1], '.'))) != NULL)
	{
		if (ft_strncmp(line, ".cub", 4) != 0)
			ft_error("Wrong file extension, please use .cub\n", env);
	}
	else
		ft_error("Wrong file extension, please use .cub\n", env);
	close(fd);
}

int		main(int argc, char **argv)
{
	t_env *env;

	if ((env = env_alloc()) == NULL)
		ft_error("failed to allocate env\n", env);
//	check_arg(env, argc, argv);
//	check_fd(argv, env);
	init_conf(env->conf);
	if (!(env->conf->file = ft_strdup(argv[1])))
		ft_error("failed to allocate conf.file\n", env);
	launch_game(env);
	ft_clear_env(env);
	exit(0);
	return (0);
}
