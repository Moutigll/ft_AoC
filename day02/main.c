/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 14:34:22 by ele-lean          #+#    #+#             */
/*   Updated: 2024/12/02 16:49:00 by ele-lean         ###   ########.fr       */
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
		free_tab(tmp->content);
		free(tmp);
	}
}

int	compute_list(t_list *list)
{
	int	stable;
	int	i;
	int	order;

	stable = 0;
	while (list)
	{
		order = is_sorted(list->content);
		if (has_duplicates(list->content) || !order)
		{
			list = list->next;
			continue ;
		}
		i = 0;
		while (((char **)list->content)[i + 1] &&
			check_values(atoi(((char **)list->content)[i]),
				atoi(((char **)list->content)[i + 1]), order))
			i++;
		if (!((char **)list->content)[i + 1])
			stable++;
		list = list->next;
	}
	return (stable);
}

int	process_report(char **content)
{
	int	i;
	int	order;

	order = is_sorted(content);
	if (has_duplicates(content) || !order)
		return (0);
	i = 0;
	while (content[i + 1]
		&& check_values(atoi(content[i]), atoi(content[i + 1]), order))
		i++;
	return (content[i + 1] == NULL);
}

int	compute_list2(t_list *list)
{
	int		stable;
	int		j;
	char	**content;

	stable = 0;
	while (list)
	{
		j = len(list->content);
		while (j--)
		{
			content = get_content(list->content, j);
			if (!content)
				continue ;
			if (process_report(content))
			{
				stable++;
				free(content);
				break ;
			}
			free(content);
		}
		list = list->next;
	}
	return (stable);
}

int	main(void)
{
	int		fd;
	t_list	*list;

	fd = open("day02/input.txt", O_RDONLY);
	if (fd == -1)
	{
		ft_printf("Error opening file\n");
		return (1);
	}
	list = NULL;
	get_list(&list, fd);
	ft_printf("Number of safe reports: %d\n", compute_list(list));
	ft_printf("Number of safe reports after using the Problem Dampener: %d\n",
		compute_list2(list));
	close(fd);
	free_list(list);
	return (0);
}
