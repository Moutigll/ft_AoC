/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 06:10:00 by ele-lean          #+#    #+#             */
/*   Updated: 2024/12/10 09:53:33 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	insert_new_entry(int ***tab, int i, int size, int old_size)
{
	int	tmp;
	int	j;

	tmp = *(tab[i][0]) - *(tab[size][0]);
	*(tab[i][0]) = *(tab[size][0]);
	*(tab[i][1]) = *(tab[size][1]);
	*(tab[size][1]) = -1;
	old_size++;
	j = old_size;
	while (j > i)
	{
		tab[j] = tab[j - 1];
		j--;
	}
	tab[i + 1] = malloc(sizeof(int *) * 2);
	tab[i + 1][0] = malloc(sizeof(int));
	tab[i + 1][1] = malloc(sizeof(int));
	*(tab[i + 1][0]) = tmp;
	*(tab[i + 1][1]) = -1;
	return (old_size);
}

void	update_tab(int ***tab, int *size, int *old_size)
{
	int	i;

	i = 0;
	while (i < *size)
	{
		if (*(tab[i][1]) == -1 && *(tab[i][0]) >= *(tab[*size][0]))
		{
			if (*(tab[i][0]) == *(tab[*size][0]))
			{
				*(tab[i][1]) = *(tab[*size][1]);
				*(tab[*size][1]) = -1;
				break ;
			}
			else
			{
				*old_size = insert_new_entry(tab, i, *size, *old_size);
				break ;
			}
		}
		i++;
	}
}

void	compress_disk(int ***tab, int size)
{
	int	old_size;

	old_size = size;
	while (size > 0)
	{
		update_tab(tab, &size, &old_size);
		size--;
		while (size > 0 && *(tab[size][1]) == -1)
			size--;
	}
}

long int	compress_map(char *disk, int size, int i)
{
	long int	total;
	int			index;
	int			j;

	total = 0;
	index = 0;
	while (disk[i])
	{
		j = disk[i] - '0';
		while (j--)
			total += (index++) * (i / 2);
		i += 2;
		while (disk[i - 1] - '0' && i - 1 < size)
		{
			while (disk[size] - '0' && disk[i - 1] - '0')
			{
				total += (index++) * (size / 2);
				disk[i - 1]--;
				disk[size]--;
			}
			if (disk[size] == '0')
				size -= 2;
		}
	}
	return (total);
}

int	main(void)
{
	int		fd;
	char	*line;
	int		size;
	int		***tab;

	fd = open("day09/input.txt", O_RDONLY);
	if (fd < 0)
		return (1);
	line = get_next_line(fd);
	if (!line)
	{
		perror("Failed to read line");
		return (close(fd));
	}
	close(fd);
	size = ft_strlen(line);
	size -= 2;
	tab = gen_tab(line, size + 1);
	printf("Part 1: %ld\n", compress_map(line, size, 0));
	(void)tab;
	compress_disk(tab, size);
	printf("Part 2: %ld\n", get_checksum(tab, size));
	free_disk(tab, size * 2);
	free(line);
}
