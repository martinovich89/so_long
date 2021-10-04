/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhenry <mhenry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 00:07:02 by martin            #+#    #+#             */
/*   Updated: 2021/10/01 16:10:46 by mhenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

void	ft_clear_conf(t_env *env)
{
	if (env->conf->map)
		ft_arrdel((void ***)&env->conf->map);
	if (env->conf->file)
		ft_memdel((void **)&env->conf->file);
	if (env->conf)
		ft_memdel((void **)&env->conf);
}

void	ft_clear_tex(t_env *env)
{
	size_t i;

	i = 0;
	while (i < 4)
	{
		if (env->tex[i].img)
		{
			mlx_destroy_image(env->mlx, env->tex[i].img);
			env->tex[i].img = NULL;
		}
		i++;
	}
}

void	ft_clear_env(t_env *env)
{
	if (env)
	{
		if (env->sheet)
			ft_arrdel((void ***)&env->sheet);
		if (env->conf)
			ft_clear_conf(env);
		if (env->tex[0].addr)
			ft_clear_tex(env);	
		if (env->sp.tex.img)
			mlx_destroy_image(env->mlx, env->sp.tex.img);
		if (env->mlx && env->tex[0].img)
			ft_clear_tex(env);
		if (env->mlx && env->win && env->img.img)
			mlx_destroy_image(env->mlx, env->img.img);
		if (env->mlx && env->win)
			mlx_destroy_window(env->mlx, env->win);
		if (env->mlx)
		{
			mlx_destroy_display(env->mlx);
			mlx_loop_end(env->mlx);
			free(env->mlx);
			env->mlx = NULL;
		}
		free(env);
	}
}

int		map_too_small(char **map)
{
	size_t i;
	size_t j;
	size_t count;

	count = 0;
	i = 0;
	j = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
			j++;
		if (j > 2)
			count++;
		i++;
	}
	return (count < 3);
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
	size_t width;
	size_t height;

	i = 0;
	width = ft_strlen(map[0]);
	while (map[i])
		i++;
	height = i;
	if (!is_charset_str(map[0], "1"))
		return (1);
	i = 0;
	while (i < height - 1)
	{
		if (map[i][0] != '1' || map[i][width - 1] != '1')
			return (1);
		i++;
	}
	if (!is_charset_str(map[height - 1], "1"))
		return (1);
	return (0);
}

int		check_map(t_env *env)
{
	if (map_too_small(env->conf->map))
		ft_error("map too small", env);
	if (map_not_rectangular(env->conf->map))
		ft_error("map not rectangular", env);
	if (wrong_character(env->conf->map))
		ft_error("wrong character in map description", env);
	if (not_well_circled(env->conf->map))
		ft_error("map not circled by only character '1'", env);
	return (0);
}

void	move_left(t_map *map, int *left)
{
	if (map->map[map->hero_pos[1]][map->hero_pos[0] - 1] != '1')
	{
		map->hero_pos[0]--;
		map->move_count++;
		if (map->map[map->hero_pos[1]][map->hero_pos[0]] == 'C')
		{
			map->map[map->hero_pos[1]][map->hero_pos[0]] = '0';
			map->collectibles++;
		}
	}
	*left = 0;
}

void	move_right(t_map *map, int *right)
{
	if (map->map[map->hero_pos[1]][map->hero_pos[0] + 1] != '1')
	{
		map->hero_pos[0]++;
		map->move_count++;
		if (map->map[map->hero_pos[1]][map->hero_pos[0]] == 'C')
		{
			map->map[map->hero_pos[1]][map->hero_pos[0]] = '0';
			map->collectibles++;
		}
	}
	*right = 0;
}

void	move_down(t_map *map, int *down)
{
	if (map->map[map->hero_pos[1] + 1][map->hero_pos[0]] != '1')
	{
		map->hero_pos[1]++;
		map->move_count++;
		if (map->map[map->hero_pos[1]][map->hero_pos[0]] == 'C')
		{
			map->map[map->hero_pos[1]][map->hero_pos[0]] = '0';
			map->collectibles++;
		}
	}
	*down = 0;
}

void	move_up(t_map *map, int *up)
{
	if (map->map[map->hero_pos[1] - 1][map->hero_pos[0]] != '1')
	{
		map->hero_pos[1]--;
		map->move_count++;
		if (map->map[map->hero_pos[1]][map->hero_pos[0]] == 'C')
		{
			map->map[map->hero_pos[1]][map->hero_pos[0]] = '0';
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

void			my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bpp / 8));
	color = *(unsigned int *)dst;
}

void			draw_image(t_env *env, t_data *data, unsigned int **tab)
{
	unsigned int x;
	unsigned int y;

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

void	next_tex(t_env *env, size_t i, size_t j)
{
	if (env->conf->map[i][j] == 'H')
		env->cur_tex = env->tex + 0;
	else if (env->conf->map[i][j] == '1')
		env->cur_tex = env->tex + 1;
	else if (env->conf->map[i][j] == 'E')
		env->cur_tex = env->tex + 2;
	else if (env->conf->map[i][j] == 'C')
		env->cur_tex = env->tex + 3;
	else
		env->cur_tex = NULL;
}	

int		pick_tex_color(t_env *env, size_t i, size_t j)
{
	unsigned int color;
	char *dst;

	if (!env->cur_tex)
		color = 0x00808080;
	else
	{
		dst = env->cur_tex->addr + (i * env->cur_tex->line_length + j * env->cur_tex->bpp / 8);
		color = *(unsigned int *)dst;
	}
	return (color);
}

void	draw_sheet(t_env *env, unsigned int **sheet)
{
	size_t i;
	size_t j;

	i = 0;
	j = 0;
	while (i < env->conf->res_h - 1)
	{
		j = 0;
		while (j < env->conf->res_w - 1)
		{
			if (j % 50 == 0)
				next_tex(env, i / 50, j / 50);
			sheet[i][j] = pick_tex_color(env, i / 50, j / 50);
			printf("%x\n", sheet[i][j]);
			j++;
		}
		i++;
	}
}

void	reset_sheet(t_env *env)
{
	size_t i;
	size_t j;

	i = 0;
	while (i < env->conf->res_h - 1)
	{
		j = 0;
		while (j < env->conf->res_w - 1)
		{
			env->sheet[i][j] = 0;
			j++;
		}
		i++;
	}
}

int		render_next_frame(t_env *env)
{
	reset_sheet(env);
	update_hero_pos(env, env->map);
	draw_sheet(env, env->sheet);
	//guards_pos(env);
	draw_image(env, &env->img, env->sheet);
	mlx_put_image_to_window(env->mlx, env->win, env->img.img, 0, 0);
	return (0);
}

void	map_len(t_env *env, int fd)
{
	char *line;
	size_t i;
	size_t max;

	i = 0;
	max = 0;
	while (get_next_line(fd, &line) > 0)
	{
		if (max < ft_strlen(line))
			max = ft_strlen(line);
		if (line)
			i++;
		ft_memdel((void **)&line);
	}
	ft_memdel((void **)&line);
	env->conf->map_h = i;
	env->conf->map_w = max;
}

void	parse_map(t_env *env)
{
	int fd;
	size_t i;

	fd = open(env->conf->file, O_RDONLY);
	map_len(env, fd);
	if (set_to_zero(sizeof(char *) * (env->conf->map_h + 1), &env->conf->map))
		ft_error("Failed allocation\n", env);
	i = 0;
	close(fd);
	fd = open(env->conf->file, O_RDONLY);
	while (get_next_line(fd, env->conf->map + i) > 0)
	{
		if (!env->conf->map[i])
			ft_error("Failed allocation\n", env);
		i++;
	}
	if (env->conf->map + i)
		ft_memdel((void **)env->conf->map + i);
	get_next_line(-1, NULL);
	close(fd);
}

void	set_player_pos(t_env *env)
{
	size_t i;
	size_t j;

	i = 0;
	while (env->conf->map[i])
	{
		j = 0;
		while (env->conf->map[i][j])
		{
			if (env->conf->map[i][j] == 'H')
			{
				env->hero_pos[0] = j;
				env->hero_pos[1] = i;
			}
			j++;
		}
		i++;
	}
}

void	set_conf(t_env *env)
{
	env->conf->res_h = env->conf->map_h * 50;
	env->conf->res_w = env->conf->map_w * 50;
	set_player_pos(env);
	env->conf->path_he = "textures/Hero1.xpm";
	env->conf->path_ex = "textures/Exit.xpm";
	env->conf->path_wa = "textures/Wall.xpm";
	env->conf->path_it = "textures/Treasure.xpm";
}

void	init_textures2(t_env *env)
{
	env->tex[2].img = mlx_xpm_file_to_image(
		env->mlx, env->conf->path_wa, &env->tex[2].w, &env->tex[2].h);
	if (!env->tex[2].img)
		ft_error("failed to allocate tex[2].img\n", env);
	env->tex[2].addr = mlx_get_data_addr(
		env->tex[2].img, &env->tex[2].bpp, &env->tex[2].line_length, &env->tex[2].endian);
	if (!env->tex[2].addr)
		ft_error("failed to allocate tex[2].addr\n", env);
	env->tex[3].img = mlx_xpm_file_to_image(
		env->mlx, env->conf->path_ex, &env->tex[3].w, &env->tex[3].h);
	if (!env->tex[3].img)
		ft_error("failed to allocate tex[3].img\n", env);
	env->tex[3].addr = mlx_get_data_addr(
		env->tex[3].img, &env->tex[3].bpp, &env->tex[3].line_length, &env->tex[3].endian);
	if (!env->tex[3].addr)
		ft_error("failed to allocate tex[3].addr\n", env);
}

void	init_textures1(t_env *env)
{
	env->tex[0].img = mlx_xpm_file_to_image(
		env->mlx, env->conf->path_he, &env->tex[0].w, &env->tex[0].h);
	if (!env->tex[0].img)
		ft_error("failed to allocate tex[0].img\n", env);
	env->tex[0].addr = mlx_get_data_addr(
		env->tex[0].img, &env->tex[0].bpp, &env->tex[0].line_length, &env->tex[0].endian);
	if (!env->tex[0].addr)
		ft_error("failed to allocate tex[0].addr\n", env);
	env->tex[1].img = mlx_xpm_file_to_image(
		env->mlx, env->conf->path_it, &env->tex[1].w, &env->tex[1].h);
	if (!env->tex[1].img)
		ft_error("failed to allocate tex[1].img\n", env);
	env->tex[1].addr = mlx_get_data_addr(
		env->tex[1].img, &env->tex[1].bpp, &env->tex[1].line_length, &env->tex[1].endian);
	if (!env->tex[1].addr)
		ft_error("failed to allocate tex[1].addr\n", env);
}

void	my_mlx_init(t_env *env)
{
	if (!(env->mlx = mlx_init()))
		ft_error("failed to allocate mlx\n", env);
	env->win = mlx_new_window(env->mlx
		, env->conf->res_w, env->conf->res_h, "cub3D");
	if (!env->win)
		ft_error("failed to allocate win\n", env);
	env->img.img = mlx_new_image(
		env->mlx, env->conf->res_w, env->conf->res_h);
	if (!env->img.img)
		ft_error("failed to allocate img.img\n", env);
	env->img.addr = mlx_get_data_addr(
		env->img.img, &env->img.bpp, &env->img.line_length, &env->img.endian);
	if (!env->img.addr)
		ft_error("failed to allocate img.addr\n", env);
	init_textures1(env);
	init_textures2(env);
	if (ft_build_arr((void ***)&env->sheet, sizeof(unsigned int), env->conf->res_w, env->conf->res_h))
		ft_error("failed sheet allocation\n", env);
	if (!env->sheet)
		ft_error("failed to allocate rndr->sheet\n", env);
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

int		set_to_zero(size_t size, void *ptr)
{
	void	**deref;

	deref = (void **)ptr;
	*deref = ft_calloc(1, size);
	if (!(*deref))
		return (1);
	return (0);
}

int		main(int argc, char **argv)
{
	t_env *env;

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
