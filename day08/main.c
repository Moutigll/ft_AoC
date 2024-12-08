/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 06:01:29 by ele-lean          #+#    #+#             */
/*   Updated: 2024/12/08 10:15:47 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	free_antinode(void *antinode)
{
	free(antinode);
}

int	add_antinode(t_list **antinodes_list,
	t_antinode antinode, int width, int height)
{
	t_list		*current;
	t_antinode	*new_antinode;

	if (antinode.x < 0 || antinode.x >= width
		|| antinode.y < 0 || antinode.y >= height)
		return (0);
	current = *antinodes_list;
	while (current)
	{
		if (((t_antinode *)(current->content))->x == antinode.x
			&& ((t_antinode *)(current->content))->y == antinode.y)
			return (0);
		current = current->next;
	}
	new_antinode = malloc(sizeof(t_antinode));
	if (!new_antinode)
		return (0);
	new_antinode->x = antinode.x;
	new_antinode->y = antinode.y;
	ft_lstadd_back(antinodes_list, ft_lstnew(new_antinode));
	return (1);
}

char	**read_map(int fd, int height)
{
	char	**map;
	char	*line;
	int		i;

	map = malloc(sizeof(char *) * (height + 1));
	if (!map)
	{
		printf("Error\n");
		return (NULL);
	}
	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		map[i] = line;
		i++;
		line = get_next_line(fd);
	}
	map[i] = NULL;
	return (map);
}

int	main(void)
{
	char	**map;
	int		fd;
	int		height;

	height = ft_getnline("day08/input.txt");
	fd = open("day08/input.txt", O_RDONLY);
	if (fd == -1)
		return ((printf("Error: Unable to open the file.\n")), 1);
	map = read_map(fd, height);
	if (!map)
		return ((close(fd)), 1);
	compute(map, height, 0);
	close(fd);
	free_tab((void **)map);
	fd = open("day08/input.txt", O_RDONLY);
	if (fd == -1)
		return ((printf("Error: Unable to open the file.\n")), 1);
	map = read_map(fd, height);
	compute(map, height, 1);
	free_tab((void **)map);
	fd = open("day08/input.txt", O_RDONLY);
	return (0);
}
