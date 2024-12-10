/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 06:18:43 by ele-lean          #+#    #+#             */
/*   Updated: 2024/12/10 10:50:22 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "libft.h"

typedef struct s_coord
{
	int	x;
	int	y;
}	t_coord;

typedef struct s_find_co_params
{
	int		height;
	int		width;
	int		mode;
	t_list	**visited;
}	t_find_co_params;

int		get_map(char **map);
void	add_co(t_list **list, int x, int y, int mode);
int		get_trails(char **map, int height, int width, int mode);
int		search_trails(char **map, t_list **trails, t_find_co_params *params);
void	find_co(char **map, t_list **list, t_find_co_params *params, t_coord co);