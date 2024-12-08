/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 06:34:09 by ele-lean          #+#    #+#             */
/*   Updated: 2024/12/08 06:32:05 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	parse_rules(t_list **rules, int fd)
{
	char	*line;
	int		*tab;
	char	**split_line;

	line = get_next_line(fd);
	while (line[0] != '\n')
	{
		tab = malloc(sizeof(int) * 2);
		split_line = ft_split(line, '|');
		if (split_line != NULL)
		{
			tab[0] = ft_atoi(split_line[0]);
			tab[1] = ft_atoi(split_line[1]);
			ft_lstadd_back(rules, ft_lstnew(tab));
			free_tab((void **)split_line);
		}
		free(line);
		line = get_next_line(fd);
	}
	free(line);
}

void	parse_updates(t_list **updates, int fd)
{
	char	*line;
	int		*tab;
	int		i;
	char	**split_line;

	line = get_next_line(fd);
	while (line)
	{
		split_line = ft_split(line, ',');
		if (split_line != NULL)
		{
			tab = malloc(sizeof(int) * (ft_tablen((void **)split_line) + 1));
			i = 0;
			while (split_line[i])
			{
				tab[i] = ft_atoi(split_line[i]);
				i++;
			}
			tab[i] = -1;
			ft_lstadd_back(updates, ft_lstnew(tab));
			free_tab((void **)split_line);
		}
		free(line);
		line = get_next_line(fd);
	}
}

void	parse_input(t_list **rules, t_list **updates)
{
	int		fd;

	fd = open("day05/input.txt", O_RDONLY);
	if (fd == -1)
	{
		printf("Error\n");
		return ;
	}
	parse_rules(rules, fd);
	parse_updates(updates, fd);
	close(fd);
}
