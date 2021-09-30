/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_build_arr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhenry <mhenry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 17:56:45 by mhenry            #+#    #+#             */
/*   Updated: 2021/09/30 18:02:41 by mhenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void    ft_build_arr(void ***arr, size_t size, size_t x, size_t y)
{
    size_t i;

    *arr = ft_calloc(x, sizeof(void *));
    i = 0;
    while (i < x)
    {
        ft_calloc(y, size);
        i++;
    }
    (*arr)[i] = NULL;
}