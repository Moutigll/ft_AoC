/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_part2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 23:06:29 by ele-lean          #+#    #+#             */
/*   Updated: 2024/12/07 01:06:27 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_list	*compute_path(char **map)
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
			visited_count += add_to_visited(&co_visited, *guard, 3);
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
	return (co_visited);
}



int	check_for_loop(char **map)
{
	t_list	*co_visited;
	t_coord	*guard;
	t_coord	directions[4];
	int		current_direction;
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
			guard->direction = current_direction;
			if (!add_to_visited(&co_visited, *guard, 1))
			{
				free(guard);
				free_list(co_visited);
				return (1);
			}
		}
		else
		{
			if (new_position.x < 0 || new_position.y < 0
				|| !map[new_position.y] || map[new_position.y][new_position.x] == '\0')
				break ;
			current_direction = (current_direction + 1) % 4;
		}
	}
	free(guard);
	free_list(co_visited);
	return (0);
}


int compute_loop(char **map)
{
	t_list *co_visited;
	int loop_count = 0;
	int total_tested = 0;  // Compteur des blocs testés
	t_list *temp;
	int total_blocks;

	co_visited = compute_path(map);

	// Ignorer le premier élément de la liste
	if (co_visited != NULL)
	{
		temp = co_visited;
		co_visited = co_visited->next;  // Avancer au deuxième élément
		free(temp->content);
		free(temp);
	}

	// Compter le nombre total de blocs dans la liste
	total_blocks = 0;
	t_list *count_temp = co_visited;
	while (count_temp != NULL)
	{
		total_blocks++;
		count_temp = count_temp->next;
	}

	// Maintenant, commencer à itérer à partir du deuxième élément
	while (co_visited != NULL)
	{
		t_coord *coord = (t_coord *)co_visited->content;
		int y = coord->y;
		int x = coord->x;
		map[y][x] = '#';
		loop_count += check_for_loop(map);
		map[y][x] = '.';

		// Incrémenter le compteur des blocs testés
		total_tested++;

		system("clear");
		printf("Blocks tested: %d/%d (%.2f%%) (+1) %d\n", total_tested, total_blocks, (float)total_tested / total_blocks * 100, loop_count);

		temp = co_visited;
		co_visited = co_visited->next;
		free(temp->content);
		free(temp);
	}

	return loop_count;
}
