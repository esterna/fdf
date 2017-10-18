/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esterna <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 22:20:14 by esterna           #+#    #+#             */
/*   Updated: 2017/10/18 15:44:39 by esterna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void			fdf_exit(t_frame *frame, int i)
{
	ft_free_array((void **)frame->map, frame->map_size[1] + 1);
	ft_memdel((void **)&frame->map_size);
	if (i == 0)
		ft_putstr_fd("Error\n", 2);
	mlx_destroy_image(frame->mlx, frame->image);
	mlx_destroy_window(frame->mlx, frame->window);
	exit(1);
}
