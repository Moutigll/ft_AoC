/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 14:41:51 by ele-lean          #+#    #+#             */
/*   Updated: 2024/12/14 16:23:44 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "libft.h"

typedef struct s_robot
{
	int		pos_x;
	int		pos_y;
	int		vel_x;
	int		vel_y;
}	t_robot;

t_list	*move_robots(t_list *robots, int width, int height);
char	**initialize_map(int width, int height);
void	update_map(t_list *robots, char **map);
void	increment_quadrant(t_robot *robot,
			int width, int height, int quadrant[4]);
