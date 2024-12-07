/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   browse_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 03:21:26 by ele-lean          #+#    #+#             */
/*   Updated: 2024/12/07 03:22:05 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	initialize_values(t_path_params *params, char **map)
{
	params->directions[0].x = 0;
	params->directions[0].y = -1;
	params->directions[1].x = 1;
	params->directions[1].y = 0;
	params->directions[2].x = 0;
	params->directions[2].y = 1;
	params->directions[3].x = -1;
	params->directions[3].y = 0;
	params->current_direction = 0;
	params->guard = find_guard(map);
}

t_coord	get_new_position(t_path_params *p)
{
	t_coord	new_position;

	new_position.x = p->guard->x + p->directions[p->current_direction].x;
	new_position.y = p->guard->y + p->directions[p->current_direction].y;
	new_position.direction = p->current_direction;
	return (new_position);
}

t_list	*process_move(t_path_params *p, t_list *co_visited, int mode)
{
	p->guard->x = p->guard->x + p->directions[p->current_direction].x;
	p->guard->y = p->guard->y + p->directions[p->current_direction].y;
	p->guard->direction = p->current_direction;
	if (mode == 0)
		add_to_visited(&co_visited, *p->guard, 0);
	else
	{
		if (!add_to_visited(&co_visited, *p->guard, 1))
		{
			free(p->guard);
			free_list(co_visited);
			return (NULL);
		}
	}
	return (co_visited);
}

t_list	*explore_map(char **map, t_path_params *p, t_list *co_visited, int mode)
{
	t_coord	new_position;

	while (1)
	{
		new_position = get_new_position(p);
		if (is_valid_move(map, new_position))
		{
			co_visited = process_move(p, co_visited, mode);
			if (co_visited == NULL)
				return (NULL);
		}
		else
		{
			if (new_position.x < 0 || new_position.y < 0
				|| !map[new_position.y]
				|| map[new_position.y][new_position.x] == '\0')
				break ;
			p->current_direction = (p->current_direction + 1) % 4;
		}
	}
	return (co_visited);
}

t_list	*compute_path(char **map, int mode)
{
	t_path_params	p;
	t_list			*co_visited;

	co_visited = NULL;
	initialize_values(&p, map);
	if (!p.guard)
		return (NULL);
	add_to_visited(&co_visited, *p.guard, 0);
	co_visited = explore_map(map, &p, co_visited, mode);
	if (co_visited == NULL)
		return (NULL);
	free(p.guard);
	return (co_visited);
}
