/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esterna <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/12 20:02:27 by esterna           #+#    #+#             */
/*   Updated: 2017/10/18 16:02:18 by esterna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void			image_pixel_put(t_frame *frame, int x, int y, int color)
{
	if (0 < x && x < WIN_X && 0 < y && y < WIN_Y)
		frame->data[(x * 4) + (y * WIN_X * 4)] = (char)color;
}

double			distance(double *d_xy)
{
	double		dist;

	dist = sqrt((d_xy[0] * d_xy[0]) + (d_xy[1] * d_xy[1]));
	d_xy[0] /= dist;
	d_xy[1] /= dist;
	return (dist);
}

void			scale(double *pt, t_frame *frame)
{
	pt[0] *= frame->scale;
	pt[3] *= frame->scale;
	pt[1] *= frame->scale;
	pt[4] *= frame->scale;
}

void			translate(double *pt, t_frame *frame)
{
	pt[0] += frame->x_offset;
	pt[3] += frame->x_offset;
	pt[1] += frame->y_offset;
	pt[4] += frame->y_offset;
	pt[2] += frame->z_offset;
	pt[5] += frame->z_offset;
}

void			rotate(double *pt, t_frame *frame)
{
	if (frame->x_rot > 0.0)
	{
		pt[1] = (pt[1] * cos(frame->x_rot * (M_PI / 180.0)))
				- (pt[2] * sin(frame->x_rot * (M_PI / 180.0)));
		pt[2] = (pt[1] * sin(frame->x_rot * (M_PI / 180.0)))
				+ (pt[2] * cos(frame->x_rot * (M_PI / 180.0)));
		pt[4] = (pt[4] * cos(frame->x_rot * (M_PI / 180.0)))
				- (pt[5] * sin(frame->x_rot * (M_PI / 180.0)));
		pt[5] = (pt[4] * sin(frame->x_rot * (M_PI / 180.0)))
				+ (pt[5] * cos(frame->x_rot * (M_PI / 180.0)));
	}
	if (frame->y_rot > 0.0)
	{
		pt[0] = (pt[0] * cos(frame->y_rot * (M_PI / 180.0)))
				+ (pt[2] * sin(frame->y_rot * (M_PI / 180.0)));
		pt[2] = - (pt[0] * sin(frame->y_rot * (M_PI / 180.0)))
				+ (pt[2] * cos(frame->y_rot * (M_PI / 180.0)));
		pt[3] = (pt[3] * cos(frame->y_rot * (M_PI / 180.0)))
				+ (pt[5] * sin(frame->y_rot * (M_PI / 180.0)));
		pt[5] = - (pt[3] * sin(frame->y_rot * (M_PI / 180.0)))
				+ (pt[5] * cos(frame->y_rot * (M_PI / 180.0)));
	}
	if (frame->z_rot > 0.0)
	{
		pt[0] = (pt[0] * cos(frame->z_rot * (M_PI / 180.0)))
				- (pt[1] * sin(frame->z_rot * (M_PI / 180.0)));
		pt[1] = (pt[0] * sin(frame->z_rot * (M_PI / 180.0)))
				+ (pt[1] * cos(frame->z_rot * (M_PI / 180.0)));
		pt[3] = (pt[3] * cos(frame->z_rot * (M_PI / 180.0)))
				- (pt[4] * sin(frame->z_rot * (M_PI / 180.0)));
		pt[4] = (pt[3] * sin(frame->z_rot * (M_PI / 180.0)))
				+ (pt[4] * cos(frame->z_rot * (M_PI / 180.0)));
	}
}

int				print_map(void *f_tmp)
{
	int		xo;
	int		yo;
	double		x;
	double		y;
	double		*pt;
	double	d_xy[2];
	t_frame	*frame;
	double	dist;
	int			bpp;
	int			size_line;
	int			endian;

	frame = (t_frame *)f_tmp;
	mlx_destroy_image(frame->mlx, frame->image);
	frame->image = mlx_new_image(frame->mlx, WIN_X, WIN_Y);
	frame->data = mlx_get_data_addr(frame->image, &bpp, &size_line, &endian);
	pt = (double *)malloc(sizeof(double) * 6);
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
			rotate(pt, frame);
			scale(pt, frame);
			pt[1] -= pt[2] * 5;
			pt[4] -= pt[5] * 5;	
			translate(pt, frame);
			x = pt[0];
			y = pt[1];
			d_xy[0] = pt[3] - pt[0];
			d_xy[1] = pt[4] - pt[1];
			dist = distance(d_xy);
			while (dist >= 0)
			{
				image_pixel_put(frame, (int)round(x), (int)round(y), 0xFFFFFF);
				x += d_xy[0];
				y += d_xy[1];
				dist--;
			}
			xo++;
		}
		yo++;
	}
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
			rotate(pt, frame);
			scale(pt, frame);
			pt[1] -= pt[2] * 5;
			pt[4] -= pt[5] * 5;
			translate(pt, frame);
			x = pt[0];
			y = pt[1];
			d_xy[0] = pt[3] - pt[0];
			d_xy[1] = pt[4] - pt[1];
			dist = distance(d_xy);
			while (dist >= 0)
			{
				image_pixel_put(frame, (int)round(x), (int)round(y), 0xFFFFFF);
				x += d_xy[0];
				y += d_xy[1];
				dist--;
			}
			yo++;
		}
		xo++;
	}
	ft_memdel((void **)&pt);
	mlx_put_image_to_window(frame->mlx, frame->window, frame->image, 0, 0);
	return (1);
}
