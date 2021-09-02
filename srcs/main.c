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

void	move_left(t_map *map, int *left)
{
	if (map->map[map->hero_pos[1]][map->hero_pos[0] - 1] != "1")
	{
		map->hero_pos[0]--;
		map->move_count++;
		if (map->map[map->hero_pos[1]][map->hero_pos[0]] == "C")
		{
			map->map[map->hero_pos[1]][map->hero_pos[0]] == "0";
			map->collectibles++;
		}
	}
	*left = 0;
}

void	move_right(t_map *map, int *right)
{
	if (map->map[map->hero_pos[1]][map->hero_pos[0] + 1] != "1")
	{
		map->hero_pos[0]++;
		map->move_count++;
		if (map->map[map->hero_pos[1]][map->hero_pos[0]] == "C")
		{
			map->map[map->hero_pos[1]][map->hero_pos[0]] == "0";
			map->collectibles++;
		}
	}
	*right = 0;
}

void	move_down(t_map *map, int *down)
{
	if (map->map[map->hero_pos[1] + 1][map->hero_pos[0]] != "1")
	{
		map->hero_pos[1]++;
		map->move_count++;
		if (map->map[map->hero_pos[1]][map->hero_pos[0]] == "C")
		{
			map->map[map->hero_pos[1]][map->hero_pos[0]] == "0";
			map->collectibles++;
		}
	}
	*down = 0;
}

void	move_up(t_map *map, int *up)
{
	if (map->map[map->hero_pos[1] - 1][map->hero_pos[0]] != "1")
	{
		map->hero_pos[1]--;
		map->move_count++;
		if (map->map[map->hero_pos[1]][map->hero_pos[0]] == "C")
		{
			map->map[map->hero_pos[1]][map->hero_pos[0]] == "0";
			map->collectibles++;
		}
	}
	*up = 0;
}

void	update_hero_pos(t_env *env, t_map *map)
{
	if (env->left == 1)
		move_left(map, &env->left);
	if (env->right == 1)
		move_right(map, &env->right);
	if (env->down == 1)
		move_down(map, &env->down);
	if (env->up == 1)
		move_up(map, &env->up);
}

void			draw_image(t_env *env, t_data *data, unsigned int **tab)
{
	int x;
	int y;

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

unsigned int	pick_tex_color(t_env *env, size_t i, size_t j)
{
	//env->rndr->sheet[i][j] = tex->addr + i % 60 * tex_width * j % 60 * 4;
}

void	draw_sheet(t_env *env, unsigned int **sheet, t_map *map)
{
	size_t i;
	size_t j;

	i = 0;
	j = 0;
	while (i < env->conf->res_h)
	{
		j = 0;
		while (j < env->conf->res_w)
		{
			if (j % 60 == 0)
				next_tex(sheet, i, j);
			sheet[i][j] == pick_tex_color(env, i, j);
			j++;
		}
		i++;
	}
}

int		render_next_frame(t_env *env)
{
	reset_sheet(env);
	update_hero_pos(env, env->map);
	draw_sheet(env, env->rndr->sheet, env->map);
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

void	check_args(int argc, t_env *env)
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
		if (ft_strncmp(line, ".ber", 4) != 0)
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
	check_args(argc, env);
	init_conf(env->conf);
	if (!(env->conf->file = ft_strdup(argv[1])))
		ft_error("failed to allocate conf.file\n", env);
	launch_game(env);
	ft_clear_env(env);
	exit(0);
	return (0);
}
