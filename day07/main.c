/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 16:55:11 by ele-lean          #+#    #+#             */
/*   Updated: 2024/12/08 06:15:35 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

long int	*process_line_to_tab(char *line)
{
	char		**splitted;
	long int	*tab;
	int			i;

	splitted = ft_split(line, ' ');
	if (!splitted)
		return (NULL);
	tab = (long int *)malloc(sizeof(long int)
			* (ft_tablen((void **)splitted) + 1));
	if (!tab)
	{
		free_tab((void **)splitted);
		return (NULL);
	}
	i = 0;
	while (splitted[i])
	{
		tab[i] = ft_atol(splitted[i]);
		i++;
	}
	tab[i] = 0;
	free_tab((void **)splitted);
	return (tab);
}

void	parse_input(int fd, t_list **list, char *line)
{
	long int	*tab;

	while (line)
	{
		tab = process_line_to_tab(line);
		free(line);
		if (!tab)
		{
			line = get_next_line(fd);
			continue ;
		}
		ft_lstadd_back(list, ft_lstnew(tab));
		line = get_next_line(fd);
	}
}

int	main(void)
{
	int		fd;
	t_list	*list;
	char	*line;

	fd = open("day07/input.txt", O_RDONLY);
	if (fd < 0)
	{
		ft_printf("Error: open file\n");
		return (1);
	}
	list = NULL;
	line = get_next_line(fd);
	parse_input(fd, &list, line);
	printf("Part1: %ld\n", compute(list, 0));
	printf("Part2: %ld\n", compute(list, 1));
	close(fd);
	free_list(list);
	return (0);
}
