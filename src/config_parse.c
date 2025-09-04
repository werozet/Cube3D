/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzielins <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 17:38:47 by pmamala           #+#    #+#             */
/*   Updated: 2025/09/04 16:29:32 by wzielins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	process_file(int fd, t_cfg *cfg, t_player *pl)
{
	char	*line;
	int		ret;

	while (1)
	{
		line = gnl(fd);
		if (!line)
			break ;
		ret = handle_line(line, fd, cfg, pl);
		if (ret != 0)
			return (ret);
	}
	return (0);
}

int	parse_config(const char *path, t_cfg *cfg, t_player *pl)
{
	int	fd;
	int	ret;

	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		perror("open");
		return (-1);
	}
	ret = process_file(fd, cfg, pl);
	close(fd);
	if (ret > 0)
		return (0);
	if (ret < 0)
		return (-1);
	ft_putendl_fd("Error\nNo map found", 2);
	return (-1);
}
