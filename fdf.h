/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esterna <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 21:06:58 by esterna           #+#    #+#             */
/*   Updated: 2017/10/18 15:57:29 by esterna          ###   ########.fr       */
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

# define WIN_X		1800
# define WIN_Y		1200

# define ESC	53

typedef struct				s_frame
{
	void	*mlx;
	void	*window;
	void	*image;
	char	*data;
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
}							t_frame;

int				*ft_intnew(size_t size);

void			fdf_exit(t_frame *frame, int i);

int				print_map(void *frame);

void			read_map(char *file, t_frame *frame);

#endif
