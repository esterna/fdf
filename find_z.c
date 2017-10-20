/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_z.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esterna <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/19 22:07:58 by esterna           #+#    #+#             */
/*   Updated: 2017/10/19 22:47:14 by esterna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void					find_z_vals(t_frame *frame)
{
	int			z_vals[2];
	int			x;
	int			y;

	z_vals[0] = 0;
	z_vals[1] = 0;
	y = 0;
	while (y < frame->map_size[1])
	{
		x = 0;
		while (x < frame->map_size[0])
		{
			if (frame->map[y][x] > z_vals[0])
				z_vals[0] = frame->map[y][x];
			if (frame->map[y][x] < z_vals[1])
				z_vals[1] = frame->map[y][x];
			x++;
		}
		y++;
	}
	frame->z_vals = z_vals;
}
