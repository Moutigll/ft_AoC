/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 06:03:42 by ele-lean          #+#    #+#             */
/*   Updated: 2024/12/12 08:32:37 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	list_contains(t_list *list, int x, int y)
{
	t_list	*current;
	t_point	*point;

	current = list;
	while (current)
	{
		point = (t_point *)current->content;
		if (point->x == x && point->y == y)
			return (1);
		current = current->next;
	}
	return (0);
}

int	get_plot(char **map, int x, int y, int mode, t_list *visited)
{
	int	plot;
	int	value;
	t_point	*current_point;

	if (x < 0 || y < 0 || !map[y] || x >= (int)ft_strlen(map[y])
		|| map[y][x] == '\n' || map[y][x] == '#'
		|| list_contains(visited, x, y))
		return (0);
	current_point = malloc(sizeof(t_point));
	if (!current_point)
		return (0);
	current_point->x = x;
	current_point->y = y;
	ft_lstadd_back(&visited, ft_lstnew(current_point));
	plot = map[y][x];
	value = 0;
	if (mode == 2)
		map[y][x] = '#';
	if (y > 0 && map[y - 1][x] == plot)
		value += get_plot(map, x, y - 1, mode, visited);
	else if (mode == 0)
		value++;
	if (map[y + 1] && map[y + 1][x] == plot)
		value += get_plot(map, x, y + 1, mode, visited);
	else if (mode == 0)
		value++;
	if (x > 0 && map[y][x - 1] == plot)
		value += get_plot(map, x - 1, y, mode, visited);
	else if (mode == 0)
		value++;
	if (x < (int)ft_strlen(map[y]) - 1 && map[y][x + 1] == plot)
		value += get_plot(map, x + 1, y, mode, visited);
	else if (mode == 0)
		value++;
	if (mode == 1)
		value++;
	return (value);
}


int	get_price(char **map, int height)
{
	int		x;
	int		y;
	int		price;
	int		area;
	int		perimeter;
	t_list	*visited;

	y = 0;
	price = 0;
	while (y < height)
	{
		x = 0;
		while (map[y][x + 1])
		{
			if (map[y][x] != '#')
			{
				visited = NULL;
				area = get_plot(map, x, y, 1, visited);
				perimeter = get_plot(map, x, y, 0, visited);
				get_plot(map, x, y, 2, visited);
				free_list(visited);
				price += area * perimeter;
			}
			x++;
		}
		y++;
	}
	return (price);
}



int	main(void)
{
	char	**map;
	char	*line;
	int		fd;
	int		height;

	height = ft_getnline("day12/input.txt");
	map = malloc(sizeof(char *) * (height + 1));
	if (!map)
		return (1);
	map[height] = NULL;
	fd = open("day12/input.txt", O_RDONLY);
	if (fd == -1)
		return (1);
	line = get_next_line(fd);
	height = 0;
	while (line)
	{
		map[height] = line;
		height++;
		line = get_next_line(fd);
	}
	close(fd);
	ft_printf("Part 1: %d\n", get_price(map, height));
	free_tab((void **)map);
	return (0);
}
