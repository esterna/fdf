/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esterna <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/19 20:46:26 by esterna           #+#    #+#             */
/*   Updated: 2017/10/19 21:16:08 by esterna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void			translate(double *pt, t_frame *frame)
{
	pt[0] += frame->x_offset;
	pt[3] += frame->x_offset;
	pt[1] += frame->y_offset;
	pt[4] += frame->y_offset;
	pt[2] += frame->z_offset;
	pt[5] += frame->z_offset;
}

void			scale(double *pt, t_frame *frame)
{
	pt[0] *= frame->scale;
	pt[3] *= frame->scale;
	pt[1] *= frame->scale;
	pt[4] *= frame->scale;
	pt[1] -= pt[2] * 5;
	pt[4] -= pt[5] * 5;
	translate(pt, frame);
}

void			rotate_z(double *pt, t_frame *frame)
{
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
	scale(pt, frame);
}

void			rotate_y(double *pt, t_frame *frame)
{
	if (frame->y_rot > 0.0)
	{
		pt[0] = (pt[0] * cos(frame->y_rot * (M_PI / 180.0)))
			+ (pt[2] * sin(frame->y_rot * (M_PI / 180.0)));
		pt[2] = -(pt[0] * sin(frame->y_rot * (M_PI / 180.0)))
			+ (pt[2] * cos(frame->y_rot * (M_PI / 180.0)));
		pt[3] = (pt[3] * cos(frame->y_rot * (M_PI / 180.0)))
			+ (pt[5] * sin(frame->y_rot * (M_PI / 180.0)));
		pt[5] = -(pt[3] * sin(frame->y_rot * (M_PI / 180.0)))
			+ (pt[5] * cos(frame->y_rot * (M_PI / 180.0)));
	}
	rotate_z(pt, frame);
}

void			rotate_x(double *pt, t_frame *frame)
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
	rotate_y(pt, frame);
}
