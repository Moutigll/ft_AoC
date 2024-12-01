/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 18:50:12 by ele-lean          #+#    #+#             */
/*   Updated: 2024/12/01 20:54:32 by ele-lean         ###   ########.fr       */
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

void	clean_exit(t_list *list1, t_list *list2, int fd)
{
	close(fd);
	free_list(list1);
	free_list(list2);
	exit(1);
}

void	sort_list(t_list **list)
{
	t_list	*tmp;
	t_list	*tmp2;
	int		tmp_value;

	tmp = *list;
	while (tmp->next)
	{
		tmp2 = tmp->next;
		while (tmp2)
		{
			if (*(int *)tmp2->content < *(int *)tmp->content)
			{
				tmp_value = *(int *)tmp2->content;
				*(int *)tmp2->content = *(int *)tmp->content;
				*(int *)tmp->content = tmp_value;
			}
			tmp2 = tmp2->next;
		}
		tmp = tmp->next;
	}
}

int	main(void)
{
	int		fd;
	t_list	*list1;
	t_list	*list2;

	fd = open("/home/ele-lean/adventofcode/day_one/ex1/input.txt", O_RDONLY);
	if (fd == -1)
	{
		ft_printf("Error opening file\n");
		return (1);
	}
	list1 = NULL;
	list2 = NULL;
	get_list(&list1, &list2, fd);
	sort_list(&list1);
	sort_list(&list2);
	ft_printf("%d\n%d", compute_result(list1, list2),
		compute_result2(list1, list2));
	close(fd);
	free_list(list1);
	free_list(list2);
	return (0);
}
