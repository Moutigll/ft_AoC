/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 16:38:56 by ele-lean          #+#    #+#             */
/*   Updated: 2024/12/08 06:56:20 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include "libft.h"

typedef struct s_coord
{
	int	x;
	int	y;
	int	direction;
}	t_coord;

typedef struct s_path_params
{
	t_coord		directions[4];
	int			current_direction;
	t_coord		*guard;
}	t_path_params;

typedef struct s_visited_params
{
	t_list	**co_visited;
	char	**map;
	int		*loop_count;
	int		*total_tested;
	int		total_blocks;
	t_list	*count_temp;
}	t_visited_params;

int		compute_distance(char **map);
void	compute_loop(char **map);
int		is_valid_move(char **map, t_coord move);
int		add_to_visited(t_list **co_visited, t_coord co, int mode);
t_coord	*find_guard(char **map);
void	initialize_values(t_path_params *params, char **map);
t_list	*compute_path(char **map, int mode);