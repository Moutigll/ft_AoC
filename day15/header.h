/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 09:49:05 by ele-lean          #+#    #+#             */
/*   Updated: 2024/12/15 22:02:36 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "libft.h"

typedef struct s_coord
{
	int	x;
	int	y;
}	t_coord;

typedef struct s_input
{
	char	**map;
	int		width;
	int		height;
	char	*movements;
	int		robot_x;
	int		robot_y;
	int		is_neighbour;
}				t_input;

t_input	get_input(void);
int		process_part(t_input *input, char target, int part);
void	push_boxes_ver(t_input *input,
			int x, int y, int *direction);
int		is_pushable(t_input *input, int x, int y, int *direction);
int		push_boxes_hor(t_input *input, int x, int y, int *direction);
void	handle_movement(t_input *input,
			char movement, int direction[4][2], int part);
int		calculate_total(t_input *input, char target);