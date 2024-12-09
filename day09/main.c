/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 06:10:00 by ele-lean          #+#    #+#             */
/*   Updated: 2024/12/09 09:43:05 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <stdio.h>

int	compress_map(char *disk, int size)
{
	int	total;
	int	index;
	int	i;
	int	j;

	i = 0;
	total = 0;
	index = 0;
	while (disk[i])
	{
		j = disk[i] - '0';
		while (j--)
		{
			total += index * (i / 2);
			index++;
		}
		i++;
		while (disk[i] - '0' && i < size)
		{
			while (disk[size] - '0' && disk[i] - '0')
			{
				total += index * (size / 2);
				index++;
				disk[i]--;
				disk[size]--;
			}
			if (disk[size] == '0')
				size -= 2;
		}
		i++;
	}
	return (total);
}



int	main(void)
{
	int		fd;
	char	*line;
	int		size;

	fd = open("day09/input.txt", O_RDONLY);
	if (fd < 0)
		return ((perror("Failed to open file")), 1);
	line = get_next_line(fd);
	if (!line)
	{
		perror("Failed to read line");
		close(fd);
		return (1);
	}
	close(fd);
	size = ft_strlen(line);
	size -= 2;
	ft_printf("Compressed map: %d\n", compress_map(line, size));
	free(line);
	return (0);
}
