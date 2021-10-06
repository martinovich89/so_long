/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhenry <mhenry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 13:15:29 by mhenry            #+#    #+#             */
/*   Updated: 2021/10/06 13:22:25 by mhenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
	while (map[i])
	{
		j = 0;
		while (map[i][j])
			j++;
		if (j != width)
		{
			return (1);
		}
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

int		missing_character(char **map)
{
	size_t i;
	size_t j;
	int a;

	a = 0;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'P' && (a & 0x10))
        	    return (1);
        	a |= (map[i][j] == '1') << 0;
        	a |= (map[i][j] == 'P') << 4;
        	a |= (map[i][j] == 'C') << 8;
        	a |= (map[i][j] == 'E') << 12;
			j++;
		}
		i++;
	}
	return (a != 0x1111) * a;
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