/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 06:10:00 by ele-lean          #+#    #+#             */
/*   Updated: 2024/12/10 06:14:13 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	free_disk(int ***tab, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		free(tab[i][0]);
		free(tab[i][1]);
		free(tab[i]);
		i++;
	}
	free(tab);
}

int	***gen_tab(char *disk, int size)
{
	int	***tab;
	int	i;

	tab = malloc(sizeof(int **) * size);
	if (!tab)
		return (NULL);
	i = 0;
	while (i < size)
	{
		tab[i] = malloc(sizeof(int *) * 2);
		if (!tab[i])
		{
			free_disk(tab, i);
			return (NULL);
		}
		tab[i][0] = malloc(sizeof(int));
		tab[i][1] = malloc(sizeof(int));
		if (!tab[i][0] || !tab[i][1])
		{
			free_disk(tab, i);
			return (NULL);
		}
		*(tab[i][0]) = disk[i] - '0';
		*(tab[i][1]) = (i % 2 == 0) ? i / 2 : -1;
		i++;
	}
	return(tab);
}
int compress_disk(int ***tab, int size)
{
	int	i;
	int	old_size = size;

	while (size > 0)
	{
		i = 0;
		while (i < size)
		{
			if (*(tab[i][1]) == -1 && *(tab[i][0]) >= *(tab[size][0]))
			{
				if (*(tab[i][0]) == *(tab[size][0]))
				{
					*(tab[i][1]) = *(tab[size][1]);
					*(tab[size][1]) = -1;
					break;
				}
				else
				{
					int	tmp = *(tab[i][0]) - *(tab[size][0]);
					*(tab[i][0]) = *(tab[size][0]);
					*(tab[i][1]) = *(tab[size][1]);
					*(tab[size][1]) = -1;

					old_size++;
					*tab = realloc(*tab, sizeof(int **) * (old_size));
					int j = old_size - 1;
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
					break;
				}
			}
			i++;
		}
		size--;
		while (size > 0 && *(tab[size][1]) == -1)
			size--;
	}
	printf("\nDisk state after compression:\n");
	return (old_size);
}


long int	get_checksum(int ***tab, int size)
{
	long int	checksum;
	int			i;
	int			index;

	checksum = 0;
	i = 0;
	index = 0;
	while (i < size)
	{
		if (*(tab[i][1]) != -1)
		{
			int j = 0;
			while (j < *(tab[i][0]))
			{
				checksum += *(tab[i][1]) * index;
				index++;
				j++;
			}
			
		}
		else
		{
			index += *(tab[i][0]);
		}
		i++;
	}
	return (checksum);
}

long int	compress_map(char *disk, int size)
{
	long int	total;
	int			index;
	int			i;
	int			j;

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
	int	***tab = gen_tab(line, size + 1);
	printf("Compressed map: %ld\n", compress_map(line, size));
	size = compress_disk(tab, size) -1;
	printf("Checksum: %ld\n", get_checksum(tab, size));
	free(line);
	return (0);
}
