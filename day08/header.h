/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 06:01:48 by ele-lean          #+#    #+#             */
/*   Updated: 2024/12/08 10:16:04 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "libft.h"
#include <stdio.h>

typedef struct s_antinode
{
	int	x;
	int	y;
}	t_antinode;

typedef struct s_coords
{
	int		width;
	int		height;
	int		x;
	int		y;
	int		dx;
	int		dy;
}	t_coords;

void		compute(char **map, int height, int mode);
void		free_antinode(void *antinode);
int			add_antinode(t_list **antinodes_list,
				t_antinode antinode, int width, int height);