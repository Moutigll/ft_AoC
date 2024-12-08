/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 06:01:29 by ele-lean          #+#    #+#             */
/*   Updated: 2024/12/08 07:06:21 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

char	**read_map(int fd, int height)
{
	char	**map;
	char	*line;
	int		i;

	map = malloc(sizeof(char *) * (height + 1));
	if (!map)
	{
		printf("Error\n");
		return (NULL);
	}
	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		map[i] = line;
		i++;
		line = get_next_line(fd);
	}
	map[i] = NULL;
	return (map);
}

int	main(void)
{
	char	**map;
	int		fd;
	int		height;

	height = ft_getnline("day08/input.txt");
	fd = open("day08/input.txt", O_RDONLY);
	if (fd == -1)
		return ((printf("Error: Unable to open the file.\n")), 1);
	map = read_map(fd, height);
	if (!map)
		return ((close(fd)), 1);
	int	i = 0;
	while (map[i])
	{
		ft_printf("%s\n", map[i]);
		i++;
	}
	close(fd);
	free_tab((void **)map);
	return (0);
}
