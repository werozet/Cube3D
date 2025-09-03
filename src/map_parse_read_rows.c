/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse_read_rows.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmamala <pmamala@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 21:34:44 by pmamala           #+#    #+#             */
/*   Updated: 2025/09/02 22:06:00 by pmamala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*gnl2(int fd)
{
	char	buf[1];
	char	*line;
	char	*tmp;
	int		r;

	line = NULL;
	while (1)
	{
		r = read(fd, buf, 1);
		if (r <= 0)
			break ;
		if (line)
			tmp = ft_strjoin(line, (char []){buf[0], 0});
		else
			tmp = ft_strjoin("", (char []){buf[0], 0});
		if (line)
			free(line);
		line = tmp;
		if (buf[0] == '\n')
			break ;
	}
	return (line);
}

static int	count_width(const char *s)
{
	int	i;
	int	w;

	i = 0;
	w = 0;
	while (s[i] && s[i] != '\n')
	{
		i++;
		w++;
	}
	return (w);
}

static int	add_line(char ***arr, int *h, char *line, int *maxw)
{
	char	**newarr;
	int		i;
	int		w;

	w = count_width(line);
	if (w > *maxw)
		*maxw = w;
	newarr = (char **)malloc(sizeof(char *) * (*h + 1));
	if (!newarr)
		return (-1);
	i = 0;
	while (i < *h)
	{
		newarr[i] = (*arr)[i];
		i++;
	}
	newarr[*h] = ft_strdup(line);
	if (*arr)
		free(*arr);
	*arr = newarr;
	(*h)++;
	return (0);
}

static int	read_map_lines(int fd, char ***rows, int *h, int *maxw)
{
	char	*line;

	while (1)
	{
		line = gnl2(fd);
		if (!line)
			break ;
		if (line[0] == '\0')
		{
			free(line);
			continue ;
		}
		if (add_line(rows, h, line, maxw) != 0)
		{
			free(line);
			return (-1);
		}
		free(line);
	}
	return (0);
}

int	read_all_rows(int fd, char *first, t_rows *rs)
{
	rs->rows = NULL;
	rs->h = 0;
	rs->maxw = 0;
	if (add_line(&rs->rows, &rs->h, first, &rs->maxw) != 0)
		return (-1);
	if (read_map_lines(fd, &rs->rows, &rs->h, &rs->maxw) != 0)
		return (-1);
	return (0);
}
