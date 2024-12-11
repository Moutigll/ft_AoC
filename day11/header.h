/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 06:00:02 by ele-lean          #+#    #+#             */
/*   Updated: 2024/12/11 12:04:56 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stdio.h>
#include "libft.h"

typedef struct s_cache
{
	long long int	value;
	int				depth;
	long long int	result;
	struct s_cache	*next;
}	t_cache;

int		num_size(long long int n);
void	split_number(long long int value,
			long long int *left, long long int *right);
void	free_cache(t_cache *cache);
void	cache_store(t_cache **cache, long long int value,
			int depth, long long int result);
t_cache	*cache_find(t_cache *cache, long long int value, int depth);