/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 06:02:18 by ele-lean          #+#    #+#             */
/*   Updated: 2024/12/04 08:00:11 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	free_list(t_list *list)
{
	t_list	*tmp;

	while (list)
	{
		tmp = list;
		list = list->next;
		free(tmp->content);
		free(tmp);
	}
}

t_list	*gli(t_list *lst, int index)
{
	while (index-- && lst != NULL)
		lst = lst->next;
	return (lst);
}

void	main2(t_list *list)
{
	int		rows;
	int		cols;
	char	**grid;
	int		i;

	rows = ft_lstsize(list);
	cols = ft_strlen(list->content);
	grid = malloc(rows * sizeof(char *));
	i = 0;
	while (i < rows)
	{
		grid[i] = gli(list, i)->content;
		i++;
	}
	ft_printf("Result: %d\n", count_xmas(grid, rows, cols));
	free(grid);
}

int	main(void)
{
	int		fd;
	t_list	*list;
	char	*line;

	fd = open("day04/input.txt", O_RDONLY);
	if (fd == -1)
	{
		ft_printf("Error opening file\n");
		return (1);
	}
	list = NULL;
	line = get_next_line(fd);
	while (line)
	{
		ft_lstadd_back(&list, ft_lstnew(line));
		line = get_next_line(fd);
	}
	main2(list);
	close(fd);
	free_list(list);
	return (0);
}
