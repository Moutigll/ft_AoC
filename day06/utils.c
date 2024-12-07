/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 17:02:36 by ele-lean          #+#    #+#             */
/*   Updated: 2024/12/07 03:02:59 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_coord	*find_guard(char **map)
{
	int		i;
	int		j;
	t_coord	*guard;

	i = 0;
	guard = malloc(sizeof(t_coord));
	while (map[i] != NULL)
	{
		j = 0;
		while (map[i][j] != '\0')
		{
			if (map[i][j] == '^')
			{
				guard->x = j;
				guard->y = i;
				guard->direction = 0;
				return (guard);
			}
			j++;
		}
		i++;
	}
	return (NULL);
}

int	check_if_visited(t_list *co_visited, t_coord co, int mode)
{
	t_list	*current;

	current = co_visited;
	while (current != NULL)
	{
		if (((t_coord *)current->content)->x == co.x
			&& ((t_coord *)current->content)->y == co.y)
		{
			if (((t_coord *)current->content)->direction == co.direction)
				return (0);
			if (mode == 0)
				return (0);
		}
		current = current->next;
	}
	return (1);
}

int	add_to_visited(t_list **co_visited, t_coord co, int mode)
{
	t_list	*new;
	t_coord	*new_coord;

	if (!check_if_visited(*co_visited, co, mode))
		return (0);
	new_coord = malloc(sizeof(t_coord));
	if (!new_coord)
		return (0);
	new_coord->x = co.x;
	new_coord->y = co.y;
	new_coord->direction = co.direction;
	new = malloc(sizeof(t_list));
	if (!new)
	{
		free(new_coord);
		return (0);
	}
	new->content = new_coord;
	new->next = NULL;
	ft_lstadd_back(co_visited, new);
	return (1);
}

int	is_valid_move(char **map, t_coord move)
{
	if (move.x < 0 || move.y < 0 || !map[move.y] || map[0][move.x] == '\0')
		return (0);
	if (map[move.y][move.x] == '#')
		return (0);
	return (1);
}
