/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_part1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 17:02:36 by ele-lean          #+#    #+#             */
/*   Updated: 2024/12/07 00:56:28 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	get_maph(char **map)
{
	int	i;

	i = 0;
	while (map[i] != NULL)
	{
		if (map[i][0] == '\0')
			return (i);
		i++;
	}
	return (i);
}

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


int	add_to_visited(t_list **co_visited, t_coord co, int mode)
{
	t_list	*current;
	t_list	*new;
	t_coord	*new_coord;

	current = *co_visited;
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

int	compute_distance(char **map)
{
	t_list	*co_visited;
	t_coord	*guard;
	t_coord	directions[4];
	int		current_direction;
	int		visited_count;
	t_coord	new_position;

	co_visited = NULL;
	directions[0].x = 0;
	directions[0].y = -1;
	directions[1].x = 1;
	directions[1].y = 0;
	directions[2].x = 0;
	directions[2].y = 1;
	directions[3].x = -1;
	directions[3].y = 0;
	current_direction = 0;
	visited_count = 0;
	guard = find_guard(map);
	if (!guard)
		return (0);
	add_to_visited(&co_visited, *guard, 0);
	while (1)
	{
		new_position.x = guard->x + directions[current_direction].x;
		new_position.y = guard->y + directions[current_direction].y;
		new_position.direction = current_direction;
		if (is_valid_move(map, new_position))
		{
			guard->x = new_position.x;
			guard->y = new_position.y;
			visited_count += add_to_visited(&co_visited, *guard, 0);
		}
		else
		{
			if (new_position.x < 0 || new_position.y < 0
				|| !map[new_position.y]
				|| map[new_position.y][new_position.x] == '\0')
				break ;
			current_direction = (current_direction + 1) % 4;
		}
	}
	free(guard);
	free_list(co_visited);
	return (visited_count + 1);
}

