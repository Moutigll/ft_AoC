/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 09:49:52 by ele-lean          #+#    #+#             */
/*   Updated: 2024/12/15 22:02:58 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

char	**allocate_new_map(int height, int width)
{
	char	**new_map;
	int		y;

	new_map = malloc(sizeof(char *) * (height + 1));
	if (!new_map)
		return (NULL);
	y = 0;
	while (y < height)
	{
		new_map[y] = malloc(width * 2 + 1);
		if (!new_map[y])
			return ((free_tab((void **)new_map)), NULL);
		y++;
	}
	new_map[height] = NULL;
	return (new_map);
}

char	**resize_map(char **map, int height, int width)
{
	char	**new_map;
	int		y;
	int		x;

	new_map = allocate_new_map(height, width);
	y = 0;
	while (y < height)
	{
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
	return (new_map);
}

void	execute_input(t_input input, int part)
{
	int		direction[4][2];
	char	*movements;

	direction[0][0] = -1;
	direction[0][1] = 0;
	direction[1][0] = 1;
	direction[1][1] = 0;
	direction[2][0] = 0;
	direction[2][1] = 1;
	direction[3][0] = 0;
	direction[3][1] = -1;
	movements = input.movements;
	while (*movements)
	{
		handle_movement(&input, *movements, direction, part);
		movements++;
	}
}

int	process_part(t_input *input, char target, int part)
{
	int	i;
	int	total;

	i = 0;
	while (input->map[i])
	{
		if (ft_strchr(input->map[i], '@'))
		{
			input->robot_x = ft_strchr(input->map[i], '@') - input->map[i];
			input->robot_y = i;
			break ;
		}
		i++;
	}
	execute_input(*input, part);
	total = calculate_total(input, target);
	free_tab((void **)input->map);
	free(input->movements);
	return (total);
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
