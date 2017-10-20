/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esterna <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/13 22:19:15 by esterna           #+#    #+#             */
/*   Updated: 2017/10/19 21:15:13 by esterna          ###   ########.fr       */
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

	line = NULL;
	frame->map_size = ft_intnew(2);
	fd = open(file, O_RDONLY);
	frame->map_size[0] = 0;
	frame->map_size[1] = 0;
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

void			fill_map(int fd, t_frame *frame)
{
	char	*line;
	int		x;
	int		y;
	char	*s;

	line = NULL;
	y = 0;
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
}

void			read_map(char *file, t_frame *frame)
{
	int		fd;

	find_map_size(file, frame);
	fd = open(file, O_RDONLY);
	frame->map = ft_2dintnew(frame->map_size[1], frame->map_size[0]);
	fill_map(fd, frame);
	close(fd);
}
