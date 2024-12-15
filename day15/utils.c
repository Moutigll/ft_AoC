/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 18:01:46 by ele-lean          #+#    #+#             */
/*   Updated: 2024/12/15 22:01:44 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int	add_to_map(t_input *input, char *line)
{
	char	**new_map;

	input->height++;
	new_map = realloc(input->map, sizeof(char *) * (input->height + 1));
	if (!new_map)
		return (0);
	input->map = new_map;
	input->map[input->height - 1] = line;
	input->map[input->height] = NULL;
	if (input->width == 0)
		input->width = ft_strlen(line) - 1;
	return (1);
}

static int	add_to_movements(t_input *input, char *line)
{
	char	*tmp;

	tmp = ft_strjoin(input->movements, line);
	free(input->movements);
	free(line);
	if (!tmp)
		return (0);
	input->movements = tmp;
	return (1);
}

static int	process_file(t_input *input, int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		if (line[0] == '#')
		{
			if (!add_to_map(input, line))
				return (0);
		}
		else
		{
			if (!add_to_movements(input, line))
				return (0);
		}
		line = get_next_line(fd);
	}
	return (1);
}

t_input	get_input(void)
{
	t_input	input;
	int		fd;

	input.map = NULL;
	input.width = 0;
	input.height = 0;
	input.movements = malloc(1);
	if (!input.movements)
		return (input);
	input.movements[0] = '\0';
	fd = open("day15/input.txt", O_RDONLY);
	if (fd < 0)
		return (input);
	if (!process_file(&input, fd))
	{
		close(fd);
		return (input);
	}
	close(fd);
	return (input);
}

int	calculate_total(t_input *input, char target)
{
	int	x;
	int	y;
	int	total;

	total = 0;
	y = 0;
	while (y < input->height)
	{
		x = 0;
		while (x < input->width)
		{
			if (input->map[y][x] == target)
				total += y * 100 + x;
			x++;
		}
		y++;
	}
	return (total);
}
