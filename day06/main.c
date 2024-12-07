/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 16:36:32 by ele-lean          #+#    #+#             */
/*   Updated: 2024/12/07 03:21:51 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	free_map(char **map)
{
	int	i;

	i = 0;
	if (!map)
		return ;
	while (map[i] != NULL)
	{
		free(map[i]);
		i++;
	}
	free(map);
}

void	free_list(t_list *list)
{
	t_list	*tmp;

	while (list)
	{
		tmp = list;
		list = list->next;
		free(tmp->content);
		free(tmp);
	}
}

int	get_len(void)
{
	int		fd;
	int		len;
	char	*line;

	fd = open("day06/input.txt", O_RDONLY);
	if (fd == -1)
		exit(0);
	len = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		len++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (len);
}

int	main(void)
{
	int		fd;
	int		i;
	char	*line;
	char	**map;

	fd = open("day06/input.txt", O_RDONLY);
	if (fd == -1)
		return (1);
	map = malloc(sizeof(char *) * (get_len() + 1));
	if (!map)
		return (1);
	i = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		map[i] = line;
		line = get_next_line(fd);
		i++;
	}
	map[i] = NULL;
	compute_loop(map);
	close(fd);
	free_map(map);
	return (0);
}
