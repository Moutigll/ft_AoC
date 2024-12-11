/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 05:59:40 by ele-lean          #+#    #+#             */
/*   Updated: 2024/12/11 12:06:58 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <stdlib.h>
#include <stdio.h>

long long int	resolve_stone(t_cache **cache, long long int value, int depth)
{
	t_cache			*cached_result;
	long long int	result;
	long long int	left_part;
	long long int	right_part;

	if (depth == 0)
		return (1);
	cached_result = cache_find(*cache, value, depth);
	if (cached_result)
		return (cached_result->result);
	if (value == 0)
		result = resolve_stone(cache, 1, depth - 1);
	else if (num_size(value) % 2 == 0)
	{
		split_number(value, &left_part, &right_part);
		result = resolve_stone(cache, left_part, depth - 1)
			+ resolve_stone(cache, right_part, depth - 1);
	}
	else
		result = resolve_stone(cache, value * 2024, depth - 1);
	cache_store(cache, value, depth, result);
	return (result);
}

t_list	*get_list(t_list **list, char *line)
{
	char			**split;
	t_list			*new;
	long long int	*content;
	int				i;

	i = 0;
	split = ft_split(line, ' ');
	free(line);
	if (!split)
	{
		perror("Error splitting line");
		exit(EXIT_FAILURE);
	}
	while (split[i])
	{
		content = malloc(sizeof(long long int));
		if (!content)
			return (NULL);
		*content = ft_atoi(split[i]);
		new = ft_lstnew(content);
		ft_lstadd_back(list, new);
		i++;
	}
	free_tab((void **)split);
	return (*list);
}

long long int	compute_list(t_list *list, int depth)
{
	long long int	total_size;
	t_list			*current;
	long long int	*content;
	t_cache			*cache;

	cache = NULL;
	total_size = 0;
	current = list;
	while (current)
	{
		content = (long long int *)current->content;
		total_size += resolve_stone(&cache, *content, depth);
		current = current->next;
	}
	free_cache(cache);
	return (total_size);
}

int	main(void)
{
	int		fd;
	char	*line;
	t_list	*list;

	list = NULL;
	fd = open("day11/input.txt", O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening file");
		return (1);
	}
	line = get_next_line(fd);
	if (!line)
	{
		close(fd);
		perror("Error reading file");
		return (1);
	}
	get_list(&list, line);
	close(fd);
	printf("Part 1: %lld\n", compute_list(list, 25));
	printf("Part 2: %lld\n", compute_list(list, 75));
	free_list(list);
	return (0);
}
