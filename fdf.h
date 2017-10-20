/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esterna <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 21:06:58 by esterna           #+#    #+#             */
/*   Updated: 2017/10/19 22:18:09 by esterna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "mlx.h"
# include "libft.h"
# include "get_next_line.h"
# include "libftprintf.h"
# include <math.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdbool.h>

# define WIN_X				1800
# define WIN_Y				1200

typedef struct				s_frame
{
	void	*mlx;
	void	*window;
	int		**map;
	int		*map_size;
	int		valid_map;
	int		scale;
	int		x_offset;
	int		y_offset;
	int		z_offset;
	double	x_rot;
	double	y_rot;
	double	z_rot;
	int		x_move;
	int		y_move;
	int		redraw;
	int		*z_vals;
}							t_frame;

int							*ft_intnew(int size);

void						fdf_exit(t_frame *frame, int i);

void						find_z_vals(t_frame *frame);

int							print_map(void *frame);

void						print_horiz(t_frame *frame,
										double *pt, double *d_xyz);

void						print_vert(t_frame *frame,
										double *pt, double *d_xyz);

void						read_map(char *file, t_frame *frame);

void						rotate_x(double *pt, t_frame *frame);

#endif
