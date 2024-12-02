/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 19:42:12 by ele-lean          #+#    #+#             */
/*   Updated: 2024/12/02 16:49:04 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	clean_exit(t_list *list, int fd)
{
	close(fd);
	free_list(list);
	exit(1);
}

void	get_list(t_list **list, int fd)
{
	char	*row;
	char	**row_split;

	row = get_next_line(fd);
	if (!row)
	{
		ft_printf("Error: could not read from file\n");
		clean_exit(*list, fd);
	}
	while (row)
	{
		row_split = ft_split(row, ' ');
		if (!row_split)
			clean_exit(*list, fd);
		ft_lstadd_back(list, ft_lstnew(row_split));
		free(row);
		row = get_next_line(fd);
	}
}
