/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 16:36:32 by ele-lean          #+#    #+#             */
/*   Updated: 2024/12/08 06:50:31 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	main(void)
{
	int		fd;
	int		i;
	char	*line;
	char	**map;

	map = malloc(sizeof(char *) * (ft_getnline("day06/input.txt") + 1));
	if (!map)
		return (1);
	i = 0;
	fd = open("day06/input.txt", O_RDONLY);
	line = get_next_line(fd);
	if (fd == -1)
		return ((free_tab((void **)map)), 1);
	while (line != NULL)
	{
		map[i] = line;
		line = get_next_line(fd);
		i++;
	}
	map[i] = NULL;
	compute_loop(map);
	close(fd);
	free_tab((void **)map);
	return (0);
}
