/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 19:42:12 by ele-lean          #+#    #+#             */
/*   Updated: 2024/12/08 06:23:23 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	handle_error(t_list *list1, t_list *list2, int fd)
{
	ft_printf("Error: ft_split failed\n");
	clean_exit(list1, list2, fd);
}

int	*get_content_from_row(char *row, char **row_split)
{
	int	*content;

	content = (int *)malloc(sizeof(int));
	if (!content)
	{
		ft_printf("Error: malloc failed\n");
		free(row);
		free_tab((void **)row_split);
		return (NULL);
	}
	*content = ft_atoi(row_split[0]);
	return (content);
}

void	process_row(char *row, char **row_split,
			t_list **list1, t_list **list2)
{
	int	*content1;
	int	*content2;

	content1 = get_content_from_row(row, row_split);
	content2 = get_content_from_row(row, row_split + 1);
	ft_lstadd_back(list1, ft_lstnew(content1));
	ft_lstadd_back(list2, ft_lstnew(content2));
	free_tab((void **)row_split);
}

void	get_list(t_list **list1, t_list **list2, int fd)
{
	char	*row;
	char	**row_split;

	row = get_next_line(fd);
	if (!row)
	{
		ft_printf("Error: could not read from file\n");
		clean_exit(*list1, *list2, fd);
	}
	while (row)
	{
		row_split = ft_split(row, ' ');
		if (!row_split)
			handle_error(*list1, *list2, fd);
		if (!row_split[0] || !row_split[1])
		{
			ft_printf("Error: unexpected row format\n");
			free(row);
			free_tab((void **)row_split);
			clean_exit(*list1, *list2, fd);
		}
		process_row(row, row_split, list1, list2);
		free(row);
		row = get_next_line(fd);
	}
}
