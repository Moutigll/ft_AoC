/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 18:01:46 by ele-lean          #+#    #+#             */
/*   Updated: 2024/12/15 18:04:39 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_input	get_input(void)
{
	t_input	input;
	int		fd;
	char	*line;
	char	*tmp;
	char	**new_map;

	input.map = NULL;
	input.width = 0;
	input.height = 0;
	input.movements = malloc(1);
	if (!input.movements)
		return (input);
	input.movements[0] = '\0';
	fd = open("day15/input.txt", O_RDONLY);
	if (fd < 0)
	{
		free(input.movements);
		return (input);
	}
	line = get_next_line(fd);
	while (line)
	{
		if (line[0] == '#')
		{
			input.height++;
			new_map = realloc(input.map, sizeof(char *) * (input.height + 1));
			if (!new_map)
			{
				free_tab((void **)input.map);
				free(input.movements);
				free(line);
				close(fd);
				return (input);
			}
			input.map = new_map;
			input.map[input.height - 1] = line;
			input.map[input.height] = NULL;
			if (input.width == 0)
				input.width = ft_strlen(line) - 1;
		}
		else
		{
			tmp = ft_strjoin(input.movements, line);
			free(input.movements);
			free(line);
			if (!tmp)
			{
				free_tab((void **)input.map);
				close(fd);
				return (input);
			}
			input.movements = tmp;
		}
		line = get_next_line(fd);
	}
	close(fd);
	return (input);
}

int	process_part(t_input *input, char target, int part)
{
	int	i;
	int	x;
	int	y;
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
	free_tab((void **)input->map);
	free(input->movements);
	return (total);
}
