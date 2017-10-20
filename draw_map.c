/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esterna <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/12 20:02:27 by esterna           #+#    #+#             */
/*   Updated: 2017/10/19 22:46:33 by esterna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int				line_color(double z)
{
	int base_color;

	base_color = 0xFFFFFF - ((int)z * 0x010100);
	return (base_color);
}

double			distance(double *d_xyz, double *pt)
{
	double		dist;
	double		dist_z;

	d_xyz[0] = pt[3] - pt[0];
	d_xyz[1] = pt[4] - pt[1];
	dist = sqrt((d_xyz[0] * d_xyz[0]) + (d_xyz[1] * d_xyz[1]));
	d_xyz[0] /= dist;
	d_xyz[1] /= dist;
	dist_z = sqrt((d_xyz[0] * d_xyz[0]) +
			(d_xyz[1] * d_xyz[1]) + (d_xyz[2] * d_xyz[2]));
	d_xyz[2] = (pt[5] - pt[2]) / dist_z;
	d_xyz[2] = isnan(d_xyz[2]) != 0 ? 0 : d_xyz[2];
	d_xyz[2] = d_xyz[2] >= 0.0 ? -1.0 * d_xyz[2] : d_xyz[2];
	return (dist);
}

void			draw_line(t_frame *frame, double *pt, double *d_xyz)
{
	double		x;
	double		y;
	double		z;
	double		dist;

	x = pt[0];
	y = pt[1];
	z = pt[2];
	dist = distance(d_xyz, pt);
	while (dist >= 0)
	{
		if (0 < x && x < WIN_X && 0 < y && y < WIN_Y)
			mlx_pixel_put(frame->mlx, frame->window,
					(int)round(x), (int)round(y), 0x00BFFF);
		x += d_xyz[0];
		y += d_xyz[1];
		z += d_xyz[2];
		dist--;
	}
}

void			print_horiz(t_frame *frame, double *pt, double *d_xyz)
{
	int			xo;
	int			yo;

	xo = 0;
	yo = 0;
	while (yo < frame->map_size[1])
	{
		xo = 0;
		while (xo + 1 < frame->map_size[0])
		{
			pt[2] = frame->map[yo][xo];
			pt[1] = yo;
			pt[0] = xo;
			pt[5] = frame->map[yo][xo + 1];
			pt[4] = yo;
			pt[3] = xo + 1;
			rotate_x(pt, frame);
			draw_line(frame, pt, d_xyz);
			xo++;
		}
		yo++;
	}
}

void			print_vert(t_frame *frame, double *pt, double *d_xyz)
{
	int			xo;
	int			yo;

	xo = 0;
	yo = 0;
	while (xo < frame->map_size[0])
	{
		yo = 0;
		while (yo + 1 < frame->map_size[1])
		{
			pt[2] = frame->map[yo][xo];
			pt[1] = yo;
			pt[0] = xo;
			pt[5] = frame->map[yo + 1][xo];
			pt[4] = yo + 1;
			pt[3] = xo;
			rotate_x(pt, frame);
			draw_line(frame, pt, d_xyz);
			yo++;
		}
		xo++;
	}
}
