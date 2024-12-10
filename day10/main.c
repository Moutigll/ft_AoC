/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 06:19:12 by ele-lean          #+#    #+#             */
/*   Updated: 2024/12/10 10:49:32 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

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

void	find_co(char **map, t_list **list, t_find_co_params *params, t_coord co)
{
	if (co.x < 0 || co.x >= params->width || co.y < 0 || co.y >= params->height)
		return ;
	if (params->mode == 0 && is_visited(*params->visited, co.x, co.y))
		return ;
	if (map[co.y][co.x] == '9')
	{
		add_co(list, co.x, co.y, params->mode);
		return ;
	}
	if (params->mode == 0)
		mark_visited(params->visited, co.x, co.y);
	if (co.y + 1 < params->height && map[co.y + 1][co.x] == map[co.y][co.x] + 1)
		find_co(map, list, params, (t_coord){co.x, co.y + 1});
	if (co.y - 1 >= 0 && map[co.y - 1][co.x] == map[co.y][co.x] + 1)
		find_co(map, list, params, (t_coord){co.x, co.y - 1});
	if (co.x + 1 < params->width && map[co.y][co.x + 1] == map[co.y][co.x] + 1)
		find_co(map, list, params, (t_coord){co.x + 1, co.y});
	if (co.x - 1 >= 0 && map[co.y][co.x - 1] == map[co.y][co.x] + 1)
		find_co(map, list, params, (t_coord){co.x - 1, co.y});
}

int	get_trails(char **map, int height, int width, int mode)
{
	int					i;
	int					total;
	t_list				**trails;
	t_list				*visited;
	t_find_co_params	params;

	trails = malloc(sizeof(t_list *) * 1000);
	visited = NULL;
	params.visited = &visited;
	params.height = height;
	params.width = width;
	params.mode = mode;
	i = search_trails(map, trails, &params);
	total = 0;
	while (i--)
	{
		total += ft_lstsize(trails[i]);
		free_list(trails[i]);
	}
	free(trails);
	return (total);
}

int	main(void)
{
	char	**map;
	int		height;
	int		width;
	int		i;
	int		n_lines;

	n_lines = ft_getnline("day10/input.txt") + 1;
	map = malloc(sizeof(char *) * n_lines);
	if (!map)
		return (1);
	i = 0;
	while (i < n_lines)
	{
		map[i] = NULL;
		i++;
	}
	height = get_map(map);
	if (height == -1)
		return ((free_tab((void **)map)), 1);
	width = ft_strlen(map[0]);
	ft_printf("Part 1: %d\n", get_trails(map, height, width, 0));
	ft_printf("Part 2: %d\n", get_trails(map, height, width, 1));
	free_tab((void **)map);
	return (0);
}
