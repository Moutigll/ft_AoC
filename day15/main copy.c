/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main copy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 09:49:52 by ele-lean          #+#    #+#             */
/*   Updated: 2024/12/15 18:11:01 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

char	**resize_map(char **map, int height, int width)
{
	char	**new_map;
	int		y;
	int		x;

	new_map = malloc(sizeof(char *) * (height + 1));
	if (!new_map)
		return (NULL);
	y = 0;
	while (y < height)
	{
		new_map[y] = malloc(width * 2 + 1);
		if (!new_map[y])
			return ((free_tab((void **)new_map)), NULL);
		x = 0;
		while (x < width)
		{
			if (map[y][x] == '#')
				ft_memcpy(&new_map[y][x * 2], "##", 2);
			else if (map[y][x] == '.')
				ft_memcpy(&new_map[y][x * 2], "..", 2);
			else if (map[y][x] == 'O')
				ft_memcpy(&new_map[y][x * 2], "[]", 2);
			else if (map[y][x] == '@')
				ft_memcpy(&new_map[y][x * 2], "@.", 2);
			x++;
		}
		new_map[y][x * 2] = '\0';
		y++;
	}
	new_map[height] = NULL;
	return (new_map);
}

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
	int x, int y, int *direction, int is_neighbour)
{
	if (input->map[y][x] == '#' || input->map[y][x] == '.')
		return ;
	if (input->map[y][x] == '[' && !is_neighbour)
		push_boxes_ver(input, x + 1, y, direction, 1);
	if (input->map[y][x] == ']' && !is_neighbour)
		push_boxes_ver(input, x - 1, y, direction, 1);
	push_boxes_ver(input, x + direction[0], y + direction[1], direction, 0);
	input->map[y + direction[1]][x + direction[0]] = input->map[y][x];
	input->map[y][x] = '.';
}

void	execute_input(t_input input, int part)
{
	int		direction[4][2] = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};
	char	*movements;
	int		i, next_x, next_y, box_x, box_y;

	movements = input.movements;
	while (*movements)
	{
		if (*movements == '<') i = 0;
		else if (*movements == '>') i = 1;
		else if (*movements == 'v') i = 2;
		else if (*movements == '^') i = 3;
		else
		{
			movements++;
			continue ;
		}
		next_x = input.robot_x + direction[i][0];
		next_y = input.robot_y + direction[i][1];
		if (next_x < 0 || next_y < 0
			|| next_x >= input.width || next_y >= input.height)
		{
			movements++;
			continue ;
		}
		if (input.map[next_y][next_x] == '#')
		{
			movements++;
			continue ;
		}
		else if (input.map[next_y][next_x] == '.')
		{
			input.map[input.robot_y][input.robot_x] = '.';
			input.robot_x = next_x;
			input.robot_y = next_y;
			input.map[input.robot_y][input.robot_x] = '@';
		}
		else if (part == 0 && input.map[next_y][next_x] == 'O')
		{
			int x = input.robot_x + direction[i][0];
			int y = input.robot_y + direction[i][1];
			while (input.map[y][x] == 'O')
			{
				x += direction[i][0];
				y += direction[i][1];
			}
			if (input.map[y][x] == '.')
			{
				input.map[input.robot_y][input.robot_x] = '.';
				input.robot_x += direction[i][0];
				input.robot_y += direction[i][1];
				input.map[input.robot_y][input.robot_x] = '@';
				input.map[y][x] = 'O';
			}
			else if (input.map[y][x] == '#')
			{
				*input.movements++;
				continue ;
			}
		}
		else if (part == 1 && (input.map[next_y][next_x] == '['
			|| input.map[next_y][next_x] == ']'))
		{
			if (direction[i][1] == 0)
			{
				if (push_boxes_hor(&input, next_x, next_y, direction[i]))
				{
					input.map[input.robot_y][input.robot_x] = '.';
					input.robot_x = next_x;
					input.robot_y = next_y;
					input.map[input.robot_y][input.robot_x] = '@';
				}
			}
			else
			{
				if (is_pushable(&input, next_x, next_y, direction[i])
					&& ((input.map[next_y][next_x] == '['
						&& is_pushable(&input, next_x + 1, next_y, direction[i])
					) || (input.map[next_y][next_x] == ']'
					&& is_pushable(&input, next_x - 1, next_y, direction[i]))))
				{
					push_boxes_ver(&input, next_x, next_y, direction[i], 0);
					input.map[input.robot_y][input.robot_x] = '.';
					input.robot_x = next_x;
					input.robot_y = next_y;
					input.map[input.robot_y][input.robot_x] = '@';
				}
			}
		}
		movements++;
	}
}

int	main(void)
{
	t_input	input;
	char	**resized_map;
	int		total;

	input = get_input();
	total = process_part(&input, 'O', 0);
	ft_printf("Part 1: %d\n", total);
	input = get_input();
	resized_map = resize_map(input.map, input.height, input.width);
	if (!resized_map)
	{
		free_tab((void **)input.map);
		free(input.movements);
		return (1);
	}
	free_tab((void **)input.map);
	input.map = resized_map;
	input.width *= 2;
	total = process_part(&input, '[', 1);
	ft_printf("Part 2: %d\n", total);
	return (0);
}


//part 1: 1475249
//part 2: 1509724