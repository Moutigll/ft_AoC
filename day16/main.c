/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 12:26:42 by ele-lean          #+#    #+#             */
/*   Updated: 2024/12/16 16:50:40 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <limits.h>

// Structure representing a state in the maze.
typedef struct s_state
{
	int			x;
	int			y;
	int			direction; // Current direction: 0 = East, 1 = South, 2 = West, 3 = North.
	int			score;
} t_state;

// Heuristic function for A* (Manhattan distance).
int	heuristic(int x1, int y1, int x2, int y2)
{
	return (abs(x1 - x2) + abs(y1 - y2));
}

// Generate neighbors for the current state.
t_state	*generate_neighbors(t_state current, t_map map, int *count)
{
	static int	dx[] = {1, 0, -1, 0};
	static int	dy[] = {0, 1, 0, -1};
	t_state		*neighbors;
	int			nx;
	int			ny;

	neighbors = malloc(sizeof(t_state) * 3);
	*count = 0;
	nx = current.x + dx[current.direction];
	ny = current.y + dy[current.direction];
	if (nx >= 0 && ny >= 0 && nx < map.width && ny < map.height && map.map[ny][nx] != '#')
	{
		neighbors[*count] = (t_state){nx, ny, current.direction, current.score + 1};
		(*count)++;
	}
	neighbors[*count] = (t_state){current.x, current.y, (current.direction + 3) % 4, current.score + 1000};
	(*count)++;
	neighbors[*count] = (t_state){current.x, current.y, (current.direction + 1) % 4, current.score + 1000};
	(*count)++;
	return (neighbors);
}

// Priority queue structure for A* (simplified).
typedef struct s_pq_node
{
	t_state			state;
	int				priority;
	struct s_pq_node	*next;
} t_pq_node;

t_pq_node	*pq_push(t_pq_node *head, t_state state, int priority)
{
	t_pq_node	*new_node;
	t_pq_node	*current;

	new_node = malloc(sizeof(t_pq_node));
	new_node->state = state;
	new_node->priority = priority;
	new_node->next = NULL;
	if (!head || priority < head->priority)
	{
		new_node->next = head;
		return (new_node);
	}
	current = head;
	while (current->next && current->next->priority <= priority)
		current = current->next;
	new_node->next = current->next;
	current->next = new_node;
	return (head);
}

t_pq_node	*pq_pop(t_pq_node **head)
{
	t_pq_node	*node;

	if (!*head)
		return (NULL);
	node = *head;
	*head = (*head)->next;
	return (node);
}

void free_pq(t_pq_node *pq)
{
	t_pq_node *current;
	t_pq_node *temp;

	current = pq;
	while (current)
	{
		temp = current;
		current = current->next;
		free(temp);
	}
}

int a_star(t_map map)
{
	t_pq_node *pq;
	int visited[map.height][map.width][4];
	t_state start;
	t_pq_node *node;
	t_state current;
	int neighbor_count;
	t_state *neighbors;

	pq = NULL;
	for (int i = 0; i < map.height; i++)
		for (int j = 0; j < map.width; j++)
			for (int d = 0; d < 4; d++)
				visited[i][j][d] = 0;
	start = (t_state){map.start.x, map.start.y, 0, 0};
	pq = pq_push(pq, start, start.score + heuristic(start.x, start.y, map.end.x, map.end.y));
	while (pq)
	{
		node = pq_pop(&pq);
		current = node->state;
		free(node);  // Libération ici
		if (visited[current.y][current.x][current.direction])
			continue;
		visited[current.y][current.x][current.direction] = 1;
		if (current.x == map.end.x && current.y == map.end.y)
		{
			free_pq(pq);  // Libère la file de priorité restante
			return current.score;
		}
		neighbors = generate_neighbors(current, map, &neighbor_count);
		for (int i = 0; i < neighbor_count; i++)
		{
			if (!visited[neighbors[i].y][neighbors[i].x][neighbors[i].direction])
			{
				int priority = neighbors[i].score + heuristic(neighbors[i].x, neighbors[i].y, map.end.x, map.end.y);
				pq = pq_push(pq, neighbors[i], priority);
			}
		}
		free(neighbors);
	}
	free_pq(pq);  // Libère la file de priorité restante
	return -1;
}


t_map	parse_input(void)
{
	t_map	map;
	int		fd;
	char	*line;
	int		i;

	fd = open("day16/input.txt", O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening file");
		exit(1);
	}
	map.map = malloc(sizeof(char *) * (ft_getnline("day16/input.txt") + 1));
	if (!map.map)
	{
		perror("Memory allocation failed");
		exit(1);
	}
	line = get_next_line(fd);
	i = 0;
	while (line)
	{
		map.map[i] = line;
		if (ft_strpos(line, 'E') != -1)
		{
			map.end.x = ft_strpos(line, 'E');
			map.end.y = i;
		}
		if (ft_strpos(line, 'S') != -1)
		{
			map.start.x = ft_strpos(line, 'S');
			map.start.y = i;
		}
		line = get_next_line(fd);
		i++;
	}
	map.height = i;
	map.width = ft_strlen(map.map[0]) - 1;
	map.map[i] = NULL;
	close(fd);
	return (map);
}



int	main(void)
{
	t_map	map;
	int		score;

	map = parse_input();
	score = a_star(map);
	if (score != -1)
		printf("Part 1: %d\n", score);
	else
		printf("No path found!\n");
	for (int i = 0; i < map.height; i++)
		free(map.map[i]);
	free(map.map);
	return (0);
}
