/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 12:58:40 by ele-lean          #+#    #+#             */
/*   Updated: 2024/12/12 13:41:51 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	list_contains(t_list *list, int x, int y)
{
	t_list	*current;
	t_point	*point;

	current = list;
	while (current)
	{
		point = (t_point *)current->content;
		if (point->x == x && point->y == y)
			return (1);
		current = current->next;
	}
	return (0);
}

char	initialize_point(char **map,
	t_point coord, t_list **visited, t_point **current_point)
{
	char	plot;

	if (coord.x < 0 || coord.y < 0 || !map[coord.y]
		|| coord.x >= (int)ft_strlen(map[coord.y])
		|| map[coord.y][coord.x] == '\n' || map[coord.y][coord.x] == '#'
		|| list_contains(*visited, coord.x, coord.y))
		return (0);
	*current_point = malloc(sizeof(t_point));
	if (!*current_point)
		return (0);
	(*current_point)->x = coord.x;
	(*current_point)->y = coord.y;
	ft_lstadd_back(visited, ft_lstnew(*current_point));
	plot = map[coord.y][coord.x];
	return (plot);
}
