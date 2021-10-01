/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_build_arr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhenry <mhenry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 17:56:45 by mhenry            #+#    #+#             */
/*   Updated: 2021/10/01 15:29:35 by mhenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int     ft_build_arr(void ***arr, size_t size, size_t x, size_t y)
{
    size_t i;

    *arr = ft_calloc(y + 1, sizeof(void *));
    if (!*arr)
        return (1);
    i = 0;
    while (i < y)
    {
        (*arr)[i] = ft_calloc(x + 1, size);
        if (!(*arr)[i])
            return (1);
        i++;
    }
    return (0);
}