/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 09:49:05 by ele-lean          #+#    #+#             */
/*   Updated: 2024/12/15 18:05:39 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "libft.h"

typedef struct s_input
{
	char	**map;
	int		width;
	int		height;
	char	*movements;
	int		robot_x;
	int		robot_y;
}				t_input;

t_input	get_input(void);
int		process_part(t_input *input, char target, int part);
void	execute_input(t_input input, int part);