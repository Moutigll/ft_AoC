/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 14:41:03 by ele-lean          #+#    #+#             */
/*   Updated: 2024/12/14 16:23:23 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	scan_for_line(char **map, int width, int height)
{
	int		i;

	i = 0;
	while (i < height)
	{
		if (ft_strnstr(map[i], "111111111", width))
			return (1);
		i++;
	}
	return (0);
}

t_list	*sim_robot(t_list *robots, int width, int height, int seconds)
{
	int		j;

	if (!robots || width <= 0 || height <= 0 || seconds <= 0)
		return (robots);
	j = 0;
	while (j < seconds)
	{
		clear_bathroom(robots, width, height);
		robots = move_robots(robots, width, height);
		j++;
	}
	return (robots);
}

int	find_robots_in_line(t_list *robots, int width, int height)
{
	char	**map;
	int		seconds;

	map = initialize_map(width, height);
	if (!map)
		return (-1);
	seconds = 1;
	while (seconds < 10000)
	{
		initialize_map(width, height);
		simulate_robot(robots, width, height, 1);
		update_map(robots, map);
		if (scan_for_line(map, width, height))
			return (free_tab((void **)map), seconds + 100);
		seconds++;
	}
	free_tab((void **)map);
	ft_printf("No robots found in line between second 100 and 10000\n");
	return (-1);
}

int	gsf(t_list *robots, int width, int height)
{
	t_list	*current;
	t_robot	*robot;
	int		quadrant[4];

	quadrant[0] = 0;
	quadrant[1] = 0;
	quadrant[2] = 0;
	quadrant[3] = 0;
	current = robots;
	while (current)
	{
		robot = (t_robot *)current->content;
		if (robot && robot->pos_x != width / 2 && robot->pos_y != height / 2)
			increment_quadrant(robot, width, height, quadrant);
		current = current->next;
	}
	return (quadrant[0] * quadrant[1] * quadrant[2] * quadrant[3]);
}

int	main(void)
{
	t_list	*robots;
	t_robot	*robot;
	int		fd;
	char	*line;

	fd = open("day14/input.txt", O_RDONLY);
	robots = NULL;
	line = get_next_line(fd);
	while (line)
	{
		robot = (t_robot *)malloc(sizeof(t_robot));
		robot->pos_x = ft_atoi(ft_strchr(line, '=') + 1);
		robot->pos_y = ft_atoi(ft_strchr(line, ',') + 1);
		robot->vel_x = ft_atoi(ft_strchr(ft_strchr(line, '=') + 1, '=') + 1);
		robot->vel_y = ft_atoi(ft_strchr(ft_strchr(line, ',') + 1, ',') + 1);
		ft_lstadd_back(&robots, ft_lstnew(robot));
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	free(line);
	ft_printf("Part 1: %d\n", gsf(sim_robot(robots, 101, 103, 100), 101, 103));
	ft_printf("Part 2: %d\n", find_robots_in_line(robots, 101, 103));
	free_list(robots);
	return (0);
}
