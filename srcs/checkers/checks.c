/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhenry <mhenry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 13:13:18 by mhenry            #+#    #+#             */
/*   Updated: 2021/11/01 12:35:05 by mhenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_map(t_env *env)
{
	if (map_too_small(env->conf->map))
		ft_error("map too small\n", env);
	if (map_not_rectangular(env->conf->map))
		ft_error("map not rectangular. only 1 '\\n' allowed\n", env);
	if (wrong_character(env->conf->map))
		ft_error("wrong character in map description\n", env);
	if (missing_character(env->conf->map))
		ft_error("at least : '1', '0', 'P', 'C', 'E' and only one 'P'\n", env);
	if (not_well_circled(env->conf->map))
		ft_error("map not circled by only character '1'\n", env);
	return (0);
}

void	check_args(int argc, t_env *env)
{
	if (argc != 2)
		ft_error("Program must be launched with 2 arguments\n", env);
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
	ret = read(fd, buffer, 1);
	if (fd < 0 || ret < 0)
		ft_error("The file does not exist\n", env);
	line = (ft_strrchr(argv[1], '.'));
	if (line != NULL)
	{
		if (ft_strcmp(line, ".ber") != 0)
			ft_error("Wrong file extension, please use .ber\n", env);
	}
	else
		ft_error("Wrong file extension, please use .ber\n", env);
	close(fd);
}
