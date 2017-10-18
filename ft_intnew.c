/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esterna <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 22:29:28 by esterna           #+#    #+#             */
/*   Updated: 2017/10/11 22:32:24 by esterna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int				*ft_intnew(size_t size)
{
	int		*new;
	size_t	i;

	i = 0;
	new = (int *)malloc(size);
	if (new == NULL)
		return (NULL);
	while (i <= size)
		new[i++] = 0;
	return (new);
}
