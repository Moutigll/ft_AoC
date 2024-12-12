/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 06:03:29 by ele-lean          #+#    #+#             */
/*   Updated: 2024/12/12 13:41:45 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

char	initialize_point(char **map,
			t_point coord, t_list **visited, t_point **current_point);