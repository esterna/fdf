/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esterna <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 22:20:14 by esterna           #+#    #+#             */
/*   Updated: 2017/10/19 16:19:19 by esterna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void			fdf_exit(t_frame *frame, int i)
{
	ft_free_array((void **)frame->map, frame->map_size[1] + 1);
	ft_memdel((void **)&frame->map_size);
	if (i == 0)
		ft_putstr_fd("Error\n", 2);
	if (frame->window != NULL)
		mlx_destroy_window(frame->mlx, frame->window);
	free(frame);
	exit(0);
}
