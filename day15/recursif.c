/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursif.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 21:09:34 by ele-lean          #+#    #+#             */
/*   Updated: 2024/12/15 21:59:00 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	push_boxes_hor(t_input *input, int x, int y, int *direction)
{
	int	possible;

	possible = 1;
	if (input->map[y][x] == '#')
		return (0);
	if (input->map[y][x] == '.')
		return (1);
	if (input->map[y][x] == '[' || input->map[y][x] == ']')
		possible = push_boxes_hor(input,
				x + direction[0], y + direction[1], direction);
	if (possible)
	{
		input->map[y + direction[1]][x + direction[0]] = input->map[y][x];
		input->map[y][x] = '.';
		return (1);
	}
	return (0);
}

int	is_pushable(t_input *input, int x, int y, int *direction)
{
	int	pushable;

	pushable = 1;
	if (input->map[y + direction[1]][x + direction[0]] == '#')
		return (0);
	if (input->map[y + direction[1]][x + direction[0]] == '.')
		return (1);
	pushable = is_pushable(input,
			x + direction[0], y + direction[1], direction);
	if (input->map[y + direction[1]][x + direction[0]] == '[' && pushable)
		pushable = is_pushable(input,
				x + direction[0] + 1, y + direction[1], direction);
	if (input->map[y + direction[1]][x + direction[0]] == ']' && pushable)
		pushable = is_pushable(input,
				x + direction[0] - 1, y + direction[1], direction);
	return (pushable);
}

void	push_boxes_ver(t_input *input,
	int x, int y, int *direction)
{
	if (input->map[y][x] == '#' || input->map[y][x] == '.')
		return ;
	if (input->map[y][x] == '[' && !input->is_neighbour)
	{
		input->is_neighbour = 1;
		push_boxes_ver(input, x + 1, y, direction);
	}
	if (input->map[y][x] == ']' && !input->is_neighbour)
	{
		input->is_neighbour = 1;
		push_boxes_ver(input, x - 1, y, direction);
	}
	input->is_neighbour = 0;
	push_boxes_ver(input, x + direction[0], y + direction[1], direction);
	input->map[y + direction[1]][x + direction[0]] = input->map[y][x];
	input->map[y][x] = '.';
}
