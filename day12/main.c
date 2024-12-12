/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 06:03:42 by ele-lean          #+#    #+#             */
/*   Updated: 2024/12/12 13:49:07 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int get_plot(char **map, t_point coord, int mode, t_list *visited)
{
	int plot;
	int value;
	t_point *current_point;

	plot = initialize_point(map, coord, &visited, &current_point);
	if (!plot)
		return (0);
	value = 0;
	if (mode == 2)
		map[coord.y][coord.x] = '#';
	if (coord.y > 0 && map[coord.y - 1][coord.x] == plot)
		value += get_plot(map, (t_point){coord.x, coord.y - 1}, mode, visited);
	else if (mode == 0)
		value++;
	if (map[coord.y + 1] && map[coord.y + 1][coord.x] == plot)
		value += get_plot(map, (t_point){coord.x, coord.y + 1}, mode, visited);
	else if (mode == 0)
		value++;
	if (coord.x > 0 && map[coord.y][coord.x - 1] == plot)
		value += get_plot(map, (t_point){coord.x - 1, coord.y}, mode, visited);
	else if (mode == 0)
		value++;
	if (coord.x < (int)ft_strlen(map[coord.y]) - 1 && map[coord.y][coord.x + 1] == plot)
		value += get_plot(map, (t_point){coord.x + 1, coord.y}, mode, visited);
	else if (mode == 0)
		value++;
	if (mode == 1)
		value++;
	return (value);
}

int get_sides(char **map, t_point coord, t_list *visited)
{
	int value;
	t_point *current_point;
	char plot;

	plot = initialize_point(map, coord, &visited, &current_point);
	if (!plot)
		return (0);
	value = 0;
	if ((coord.y == 0 || map[coord.y - 1][coord.x] != plot) && (coord.x == 0
		|| map[coord.y][coord.x - 1] != plot))
		value++;
	else if (coord.y > 0 && map[coord.y - 1][coord.x] == plot
		&& coord.x > 0 && map[coord.y][coord.x - 1] == plot
			&& map[coord.y - 1][coord.x - 1] != plot)
		value++;
	if ((coord.y == 0 || map[coord.y - 1][coord.x] != plot)
		&& map[coord.y][coord.x + 1] != plot)
		value++;
	else if (coord.y > 0 && map[coord.y - 1][coord.x] == plot
		&& map[coord.y][coord.x + 1] == plot
			&& map[coord.y - 1][coord.x + 1] != plot)
		value++;
	if ((!map[coord.y + 1] || map[coord.y + 1][coord.x] != plot)
		&& (coord.x == 0 || map[coord.y][coord.x - 1] != plot))
		value++;
	else if (map[coord.y + 1] && map[coord.y + 1][coord.x] == plot && coord.x > 0
		&& map[coord.y][coord.x - 1] == plot
			&& map[coord.y + 1][coord.x - 1] != plot)
		value++;
	if ((!map[coord.y + 1] || map[coord.y + 1][coord.x] != plot)
		&& map[coord.y][coord.x + 1] != plot)
		value++;
	else if (map[coord.y + 1] && map[coord.y + 1][coord.x] == plot
		&& map[coord.y][coord.x + 1] == plot
			&& map[coord.y + 1][coord.x + 1] != plot)
		value++;
	if (coord.y > 0 && map[coord.y - 1][coord.x] == plot)
		value += get_sides(map, (t_point){coord.x, coord.y - 1}, visited);
	if (map[coord.y + 1] && map[coord.y + 1][coord.x] == plot)
		value += get_sides(map, (t_point){coord.x, coord.y + 1}, visited);
	if (coord.x > 0 && map[coord.y][coord.x - 1] == plot)
		value += get_sides(map, (t_point){coord.x - 1, coord.y}, visited);
	if (coord.x < (int)ft_strlen(map[coord.y]) - 1
		&& map[coord.y][coord.x + 1] == plot)
		value += get_sides(map, (t_point){coord.x + 1, coord.y}, visited);
	return (value);
}

int	get_price(char **map, int height, int mode)
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
				area = get_plot(map, (t_point){x, y}, 1, visited);
				free_list(visited);
				visited = NULL;
				if (mode == 0)
					perimeter = get_plot(map, (t_point){x, y}, 0, visited);
				else
					perimeter = get_sides(map, (t_point){x, y}, visited);
				free_list(visited);
				visited = NULL;
				get_plot(map, (t_point){x, y}, 2, visited);
				free_list(visited);
				price += area * perimeter;
			}
			x++;
		}
		y++;
	}
	return (price);
}

char	**get_map(int height)
{
	int		fd;
	char	**map;
	char	*line;
	int		i;

	map = malloc(sizeof(char *) * (height + 1));
	if (!map)
		return (NULL);
	map[height] = (NULL);
	fd = open("day12/input.txt", O_RDONLY);
	if (fd == -1)
		return (free(map), NULL);
	line = get_next_line(fd);
	i = 0;
	while (line)
	{
		map[i] = line;
		i++;
		line = get_next_line(fd);
	}
	close(fd);
	return (map);
}

int	main(void)
{
	char	**map;
	int		height;

	height = ft_getnline("day12/input.txt");
	if (height <= 0)
		return (1);
	map = get_map(height);
	if (!map)
		return (1);
	ft_printf("Part 1: %d\n", get_price(map, height, 0));
	free_tab((void **)map);
	map = get_map(height);
	if (!map)
		return (1);
	ft_printf("Part 2: %d\n", get_price(map, height, 1));
	free_tab((void **)map);	
	return (0);
}

//goal 872382
//out  871584