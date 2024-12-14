/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 16:17:46 by ele-lean          #+#    #+#             */
/*   Updated: 2024/12/14 16:23:40 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_list	*move_robots(t_list *robots, int width, int height)
{
	t_list	*current;
	t_robot	*robot;

	current = robots;
	while (current)
	{
		robot = (t_robot *)current->content;
		if (robot)
		{
			robot->pos_x = (robot->pos_x + robot->vel_x) % width;
			robot->pos_y = (robot->pos_y + robot->vel_y) % height;
			if (robot->pos_x < 0)
				robot->pos_x += width;
			if (robot->pos_y < 0)
				robot->pos_y += height;
		}
		current = current->next;
	}
	return (robots);
}

char	**initialize_map(int width, int height)
{
	char	**map;
	int		i;

	map = (char **)malloc(sizeof(char *) * (height + 1));
	if (!map)
		return (NULL);
	i = 0;
	while (i < height)
	{
		map[i] = (char *)malloc(width + 1);
		if (!map[i])
			return (free_tab((void **)map), NULL);
		ft_memset(map[i], '0', width);
		map[i][width] = '\0';
		i++;
	}
	map[height] = NULL;
	return (map);
}

void	update_map(t_list *robots, char **map)
{
	t_list	*current;
	t_robot	*robot;

	current = robots;
	while (current)
	{
		robot = (t_robot *)current->content;
		if (robot)
			map[robot->pos_y][robot->pos_x] = '1';
		current = current->next;
	}
}

void	increment_quadrant(t_robot *robot,
	int width, int height, int quadrant[4])
{
	if (robot->pos_x < width / 2 && robot->pos_y < height / 2)
		quadrant[0]++;
	else if (robot->pos_x >= width / 2 && robot->pos_y < height / 2)
		quadrant[1]++;
	else if (robot->pos_x < width / 2 && robot->pos_y >= height / 2)
		quadrant[2]++;
	else if (robot->pos_x >= width / 2 && robot->pos_y >= height / 2)
		quadrant[3]++;
}
