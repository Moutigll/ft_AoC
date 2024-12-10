/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 08:28:09 by ele-lean          #+#    #+#             */
/*   Updated: 2024/12/10 10:49:57 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

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

int	search_trails(char **map, t_list **trails, t_find_co_params *params)
{
	t_coord	co;
	int		i;

	co.y = 0;
	i = 0;
	while (co.y < params->height)
	{
		co.x = 0;
		while (co.x < params->width)
		{
			if (map[co.y][co.x] == '0')
			{
				trails[i] = NULL;
				*params->visited = NULL;
				find_co(map, &trails[i], params, co);
				free_list(*params->visited);
				i++;
			}
			co.x++;
		}
		co.y++;
	}
	return (i);
}
