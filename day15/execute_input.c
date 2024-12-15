/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 19:47:27 by ele-lean          #+#    #+#             */
/*   Updated: 2024/12/15 21:58:42 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int	get_direction(char movement)
{
	if (movement == '<')
		return (0);
	if (movement == '>')
		return (1);
	if (movement == 'v')
		return (2);
	if (movement == '^')
		return (3);
	return (-1);
}

static void	move_robot(t_input *input, t_coord next)
{
	input->map[input->robot_y][input->robot_x] = '.';
	input->robot_x = next.x;
	input->robot_y = next.y;
	input->map[input->robot_y][input->robot_x] = '@';
}

static void	move_pushable_robot(t_input *input, int *direction, t_coord next)
{
	int	x;
	int	y;

	x = next.x + direction[0];
	y = next.y + direction[1];
	while (input->map[y][x] == 'O')
	{
		x += direction[0];
		y += direction[1];
	}
	if (input->map[y][x] == '.')
	{
		move_robot(input, next);
		input->map[y][x] = 'O';
	}
}

static void	handle_pushable(t_input *input,
	int *direction, int part, t_coord next)
{
	if (part == 0 && input->map[next.y][next.x] == 'O')
	{
		move_pushable_robot(input, direction, next);
	}
	else if (part == 1 && (input->map[next.y][next.x] == '['
		|| input->map[next.y][next.x] == ']'))
	{
		if (direction[1] == 0
			&& push_boxes_hor(input, next.x, next.y, direction))
		{
			move_robot(input, next);
		}
		else if (is_pushable(input, next.x, next.y, direction)
			&& ((input->map[next.y][next.x] == '['
				&& is_pushable(input, next.x + 1, next.y, direction))
			|| (input->map[next.y][next.x] == ']'
			&& is_pushable(input, next.x - 1, next.y, direction))))
		{
			input->is_neighbour = 0;
			push_boxes_ver(input, next.x, next.y, direction);
			move_robot(input, next);
		}
	}
}

void	handle_movement(t_input *input,
	char movement, int direction[4][2], int part)
{
	int		dir;
	t_coord	next;

	dir = get_direction(movement);
	if (dir == -1)
		return ;
	next.x = input->robot_x + direction[dir][0];
	next.y = input->robot_y + direction[dir][1];
	if (next.x < 0 || next.y < 0
		|| next.x >= input->width || next.y >= input->height)
		return ;
	if (input->map[next.y][next.x] == '#')
		return ;
	if (input->map[next.y][next.x] == '.')
		move_robot(input, next);
	else
		handle_pushable(input, direction[dir], part, next);
}
