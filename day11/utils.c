/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 12:03:22 by ele-lean          #+#    #+#             */
/*   Updated: 2024/12/11 12:05:24 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_cache	*cache_find(t_cache *cache, long long int value, int depth)
{
	t_cache	*current;

	current = cache;
	while (current)
	{
		if (current->value == value && current->depth == depth)
			return (current);
		current = current->next;
	}
	return (NULL);
}

void	cache_store(t_cache **cache, long long int value,
	int depth, long long int result)
{
	t_cache	*new_entry;

	new_entry = malloc(sizeof(t_cache));
	if (!new_entry)
	{
		perror("Malloc failed for cache");
		exit(EXIT_FAILURE);
	}
	new_entry->value = value;
	new_entry->depth = depth;
	new_entry->result = result;
	new_entry->next = *cache;
	*cache = new_entry;
}

void	free_cache(t_cache *cache)
{
	t_cache	*current;
	t_cache	*tmp;

	current = cache;
	while (current)
	{
		tmp = current;
		current = current->next;
		free(tmp);
	}
}

int	num_size(long long int n)
{
	int	size;

	size = 0;
	while (n)
	{
		n /= 10;
		size++;
	}
	return (size);
}

void	split_number(long long int value,
	long long int *left, long long int *right)
{
	int				length;
	long long int	divisor;
	int				mid;

	length = num_size(value);
	divisor = 1;
	mid = length / 2;
	while (mid--)
		divisor *= 10;
	*left = value / divisor;
	*right = value % divisor;
}
