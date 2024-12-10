/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 06:19:12 by ele-lean          #+#    #+#             */
/*   Updated: 2024/12/10 08:11:36 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	add_co(t_list **list, int x, int y, int mode)
{
	t_coord	*co;
	t_list	*tmp;

	if (!list)
		return ;
	tmp = *list;
	while (tmp && mode == 0)
	{
		if (((t_coord *)tmp->content)->x == x
			&& ((t_coord *)tmp->content)->y == y)
			return ;
		tmp = tmp->next;
	}
	co = malloc(sizeof(t_coord));
	if (!co)
		return ;
	co->x = x;
	co->y = y;
	ft_lstadd_back(list, ft_lstnew(co));
}

int	is_visited(t_list *visited, int x, int y)
{
	t_list	*tmp;
	t_coord	*coord;

	tmp = visited;
	while (tmp)
	{
		coord = (t_coord *)tmp->content;
		if (coord->x == x && coord->y == y)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void	mark_visited(t_list **visited, int x, int y)
{
	t_coord	*coord;

	coord = malloc(sizeof(t_coord));
	if (!coord)
		return ;
	coord->x = x;
	coord->y = y;
	ft_lstadd_back(visited, ft_lstnew(coord));
}

void	find_co(char **map, t_list **list, t_list **visited,
	int x, int y, int height, int width, int mode)
{
	if (x < 0 || x >= width || y < 0 || y >= height)
		return ;
	if (mode == 0 && is_visited(*visited, x, y))
		return ;
	if (map[y][x] == '9')
	{
		add_co(list, x, y, mode);
		return ;
	}
	if (mode == 0)
		mark_visited(visited, x, y);
	if (y + 1 < height && map[y + 1][x] == map[y][x] + 1)
		find_co(map, list, visited, x, y + 1, height, width, mode);
	if (y - 1 >= 0 && map[y - 1][x] == map[y][x] + 1)
		find_co(map, list, visited, x, y - 1, height, width, mode);
	if (x + 1 < width && map[y][x + 1] == map[y][x] + 1)
		find_co(map, list, visited, x + 1, y, height, width, mode);
	if (x - 1 >= 0 && map[y][x - 1] == map[y][x] + 1)
		find_co(map, list, visited, x - 1, y, height, width, mode);
}

int	get_trails(char **map, int height, int width, int mode)
{
	int		x;
	int		y;
	int		i;
	int		total;
	t_list	**trails;
	t_list	*visited;

	visited = NULL;
	trails = malloc(sizeof(t_list *) * 1000);
	i = 0;
	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			if (map[y][x] == '0')
			{
				trails[i] = NULL;
				visited = NULL;
				find_co(map, &trails[i], &visited, x, y, height, width, mode);
				free_list(visited);
				i++;
			}
			x++;
		}
		y++;
	}
	total = 0;
	while (i--)
	{
		total += ft_lstsize(trails[i]);
		free_list(trails[i]);
	}
	free(trails);
	return (total);
}

int	get_map(char **map)
{
	int		fd;
	char	*line;
	int		i;

	i = 0;
	fd = open("day10/input.txt", O_RDONLY);
	if (fd == -1)
		return (-1);
	line = get_next_line(fd);
	while (line)
	{
		map[i] = line;
		i++;
		line = get_next_line(fd);
	}
	close(fd);
	return (i);
}

int	main(void)
{
	char	**map;
	int		height;
	int		width;

	map = malloc(sizeof(char *) * ft_getnline("day10/input.txt") + 1);
	if (!map)
		return (1);
	height = get_map(map);
	if (height == -1)
	{
		ft_printf("Error: could not open file.\n");
		return (1);
	}
	width = ft_strlen(map[0]);
	ft_printf("Total trails: %d\n", get_trails(map, height, width, 0));
	ft_printf("Total trails: %d\n", get_trails(map, height, width, 1));
	free_tab((void **)map);
	free(map);
	return (0);
}
