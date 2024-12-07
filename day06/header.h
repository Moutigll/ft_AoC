/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 16:38:56 by ele-lean          #+#    #+#             */
/*   Updated: 2024/12/06 23:18:26 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "libft.h"

typedef struct s_coord
{
	int	x;
	int	y;
	int	direction;
}	t_coord;

int	compute_distance(char **map);
int	compute_loop(char **map);
void	free_list(t_list *list);
int	is_valid_move(char **map, t_coord move);
int	add_to_visited(t_list **co_visited, t_coord co, int mode);
t_coord	*find_guard(char **map);