/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esterna <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 21:12:30 by esterna           #+#    #+#             */
/*   Updated: 2017/10/18 16:04:41 by esterna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int			key_controls(int key, void *tmp_fr)
{
	t_frame		*frame;

	frame = (t_frame *)tmp_fr;
	if (key == ESC)
		fdf_exit(frame, 1);
	if (key == 126)
		frame->y_offset -= 10;
	if (key == 125)
		frame->y_offset += 10;
	if (key == 123)
		frame->x_offset -= 10;
	if (key == 124)
		frame->x_offset += 10;
	if (key == 69 || key == 24)
		frame->scale += 5;
	if (key == 78 || key == 27)
		frame->scale -= 5;
	if (key == 6)
		frame->z_rot += 10;
	if (key == 0)
		frame->z_rot = (frame->z_rot == 0) ? 350 : frame->z_rot - 10;
	if (key == 7)
		frame->x_rot += 10;
	if (key == 1)
		frame->x_rot = (frame->x_rot == 0) ? 350 : frame->x_rot - 10;
	if (key == 8)
		frame->y_rot += 10;
	if (key == 2)
		frame->y_rot = (frame->y_rot == 0) ? 350 : frame->y_rot - 10;
	return (1);
}

void		frame_init(t_frame *frame, char **argv)
{
	int			bpp;
	int			size_line;
	int			endian;

	frame->mlx = mlx_init();
	frame->window = mlx_new_window(frame->mlx, WIN_X, WIN_Y, argv[1]);
	frame->valid_map = 1;
	frame->x_rot = 0;
	frame->y_rot = 0;
	frame->z_rot = 0;
	frame->image = mlx_new_image(frame->mlx, WIN_X, WIN_Y);
	frame->data = mlx_get_data_addr(frame->image, &bpp, &size_line, &endian);
}

int			main(int argc, char **argv)
{
//	t_frame		frame;
	int			fd;

	if (argc != 2 || !(ft_strstr(argv[1], ".fdf")) || (fd = open(argv[1], O_RDONLY)) < 1)
	{
	   	ft_putstr_fd("Error\n", 2);
		return (0);
	}
	close(fd);
/*	frame_init(&frame, argv);
	read_map(argv[1], &frame);
	if (frame.valid_map == 0)
		fdf_exit(&frame, 1);
	mlx_key_hook(frame.window, key_controls, (void *)&frame);
	mlx_loop_hook(frame.mlx, print_map, (void *)&frame);
	mlx_loop(frame.mlx);
	fdf_exit(&frame, 1);*/
	return (0);
}
