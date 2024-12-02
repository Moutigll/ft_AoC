/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 15:33:41 by ele-lean          #+#    #+#             */
/*   Updated: 2024/12/02 16:40:33 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	has_duplicates(char **list)
{
	int	i;
	int	j;

	i = 0;
	while (list[i])
	{
		j = i + 1;
		while (list[j])
		{
			if (!ft_strncmp(list[i], list[j], ft_strlen(list[i]))
				&& ft_strlen(list[i]) == ft_strlen(list[j]))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	is_sorted(char **list)
{
	int	i;

	i = 0;
	while (list[i + 1] && atoi(list[i]) > atoi(list[i + 1]))
		i++;
	if (!list[i + 1])
		return (1);
	i = 0;
	while (list[i + 1] && atoi(list[i]) < atoi(list[i + 1]))
		i++;
	if (!list[i + 1])
		return (2);
	return (0);
}

int	check_values(int value1, int value2, int order)
{
	int	diff;

	diff = value1 - value2;
	if (order == 1 && value1 < value2)
		return (0);
	else if (order == 0 && value1 > value2)
		return (0);
	if (diff < 0)
		diff = -diff;
	if (diff > 3 || diff == 0)
		return (0);
	return (1);
}

int	len(char **list)
{
	int	i;

	i = 0;
	while (list[i])
		i++;
	return (i);
}

char	**get_content(char **list, int size)
{
	char	**content;
	int		i;
	int		j;
	int		len_list;

	len_list = len(list);
	content = malloc(sizeof(char *) * (len_list));
	if (!content)
		return (NULL);
	i = 0;
	j = 0;
	while (list[i])
	{
		if (i != size)
		{
			content[j] = list[i];
			j++;
		}
		i++;
	}
	content[j] = NULL;
	return (content);
}
