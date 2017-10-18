/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esterna <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/13 22:19:15 by esterna           #+#    #+#             */
/*   Updated: 2017/10/17 23:59:10 by esterna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void			debug_map(t_frame *frame)
{
	int		x;
	int		y;

	y = 0;
	while (y < frame->map_size[1])
	{
		x = 0;
		while (x < frame->map_size[0])
		{
			ft_printf("%d ", frame->map[y][x]);
			x++;
		}
		ft_putchar('\n');
		y++;
	}
	ft_putchar('\n');
}

void			find_map_size(char *file, t_frame *frame)
{
	char	*line;
	int		fd;
	int		i;
	int		*tmp;

	line = NULL;
	frame->map_size = ft_intnew(sizeof(int) * 2);
	tmp = frame->map_size;
	fd = open(file, O_RDONLY);
	while (get_next_line(fd, &line) > 0)
	{
		i = 0;
		frame->map_size[1]++;
		i = ft_count_words(line);	
		if (frame->map_size[0] == 0) 
			frame->map_size[0] = i + 1;
		else if (frame->map_size[0] != i + 1)
			frame->valid_map = 0;
		ft_strdel(&line);
	}
	close(fd);
}

void			read_map(char *file, t_frame *frame)
{
	int		fd;
	char	*line;
	int		x;
	int		y;
	char	*s;
	int		**tmp;

	y = 0;
	find_map_size(file, frame);
	line = NULL;
	fd = open(file, O_RDONLY);
	frame->map = ft_2dintnew(frame->map_size[1], frame->map_size[0]);
	tmp = frame->map;
	while (get_next_line(fd, &line) > 0)
	{
		x = 0;
		s = line;
		while (*s != '\0')
		{
			frame->map[y][x] = ft_atoi(s);
			x++;
			while ((ft_isdigit(*s) == 1 || *s == '-') && *s != '\0')
				s++;
			if (*s == ',')
				s += 9;
			while (*s == ' ' && *s != '\0')
				s++;
		}
		y++;
		ft_strdel(&line);
	}
	frame->scale = ((frame->map_size[0] >= frame->map_size[1]) ? WIN_X / frame->map_size[0] : WIN_Y / frame->map_size[1]) / 2;
	frame->x_offset = (WIN_X / 2) - (frame->map_size[0] * frame->scale / 2);
	frame->y_offset = (WIN_Y / 2) - (frame->map_size[1] * frame->scale / 2);
	frame->z_offset = 0;
	close(fd);
	//debug_map(frame);
}
