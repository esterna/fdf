/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esterna <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 21:12:30 by esterna           #+#    #+#             */
/*   Updated: 2017/10/19 22:18:51 by esterna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int			print_map(void *f_tmp)
{
	double		pt[7];
	double		d_xyz[3];
	t_frame		*frame;

	frame = (t_frame *)f_tmp;
	if (frame->redraw == 1)
	{
		frame->redraw = 0;
		mlx_clear_window(frame->mlx, frame->window);
		print_horiz(frame, pt, d_xyz);
		print_vert(frame, pt, d_xyz);
	}
	return (0);
}

void		rotate_control(int key, t_frame *frame)
{
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
}

int			key_controls(int key, void *tmp_fr)
{
	t_frame		*frame;

	frame = (t_frame *)tmp_fr;
	if (key == 53)
		fdf_exit(frame, 1);
	frame->redraw = 1;
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
	if (0 <= key && key <= 8)
		rotate_control(key, frame);
	return (0);
}

void		frame_init(t_frame *frame, char **argv)
{
	frame->mlx = mlx_init();
	frame->window = mlx_new_window(frame->mlx, WIN_X, WIN_Y, argv[1]);
	frame->valid_map = 1;
	frame->x_rot = 0;
	frame->y_rot = 0;
	frame->z_rot = 0;
	frame->redraw = 1;
	frame->scale = ((frame->map_size[0] >= frame->map_size[1])
			? WIN_X / frame->map_size[0] : WIN_Y / frame->map_size[1]) / 2;
	frame->x_offset = (WIN_X / 2) - (frame->map_size[0] * frame->scale / 2);
	frame->y_offset = (WIN_Y / 2) - (frame->map_size[1] * frame->scale / 2);
	frame->z_offset = 0;
	find_z_vals(frame);
}

int			main(int argc, char **argv)
{
	t_frame		*frame;
	int			fd;

	if (argc != 2 || !(ft_strstr(argv[1], ".fdf"))
			|| (fd = open(argv[1], O_RDONLY)) < 1)
	{
		ft_putstr_fd("Error\n", 2);
		return (0);
	}
	close(fd);
	frame = (t_frame *)malloc(sizeof(t_frame));
	frame->window = NULL;
	frame->valid_map = 1;
	read_map(argv[1], frame);
	if (frame->valid_map == 0)
		fdf_exit(frame, 1);
	frame_init(frame, argv);
	mlx_key_hook(frame->window, key_controls, (void *)frame);
	mlx_loop_hook(frame->mlx, print_map, (void *)frame);
	mlx_loop(frame->mlx);
	fdf_exit(frame, 1);
	return (0);
}
