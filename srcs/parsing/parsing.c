/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhenry <mhenry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 13:47:53 by mhenry            #+#    #+#             */
/*   Updated: 2021/10/06 23:20:22 by mhenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	map_len(t_env *env, int fd)
{
	char	*line;
	size_t	i;
	size_t	max;

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
	if (line && line[0])
		i++;
	ft_memdel((void **)&line);
	env->conf->map_h = i;
	env->conf->map_w = max;
}

void	parse_map(t_env *env)
{
	int		fd;
	size_t	i;

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
	if (env->conf->map + i && !env->conf->map[i][0])
		ft_memdel((void **)env->conf->map + i);
	get_next_line(-1, NULL);
	close(fd);
}
