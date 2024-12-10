/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 08:36:45 by ele-lean          #+#    #+#             */
/*   Updated: 2024/12/10 09:31:11 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	free_tab_entry(int **entry)
{
	if (entry)
	{
		if (entry[0])
			free(entry[0]);
		if (entry[1])
			free(entry[1]);
		free(entry);
	}
}

void	free_disk(int ***tab, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		free_tab_entry(tab[i]);
		i++;
	}
	free(tab);
}

long int	get_checksum(int ***tab, int size)
{
	long int	checksum;
	int			i;
	int			index;
	int			j;

	checksum = 0;
	i = 0;
	index = 0;
	while (i < size)
	{
		if (*(tab[i][1]) != -1)
		{
			j = 0;
			while (j < *(tab[i][0]))
			{
				checksum += *(tab[i][1]) * index++;
				j++;
			}
		}
		else
			index += *(tab[i][0]);
		i++;
	}
	return (checksum);
}

static int	**create_tab_entry(int value, int index)
{
	int	**entry;

	entry = malloc(sizeof(int *) * 2);
	if (!entry)
		return (NULL);
	entry[0] = malloc(sizeof(int));
	entry[1] = malloc(sizeof(int));
	if (!entry[0] || !entry[1])
	{
		free(entry);
		return (NULL);
	}
	*(entry[0]) = value;
	if (index % 2 == 0)
		*(entry[1]) = index / 2;
	else
		*(entry[1]) = -1;
	return (entry);
}

int	***gen_tab(char *disk, int size)
{
	int	***tab;
	int	i;

	tab = malloc(sizeof(int **) * size * 2);
	if (!tab)
		return (NULL);
	i = 0;
	while (i < size)
	{
		tab[i] = create_tab_entry(disk[i] - '0', i);
		if (!tab[i])
		{
			free_disk(tab, i);
			return (NULL);
		}
		i++;
	}
	i = size;
	while (i < size * 2)
	{
		tab[i] = NULL;
		i++;
	}
	return (tab);
}
