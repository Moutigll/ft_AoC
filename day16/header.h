/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 12:26:59 by ele-lean          #+#    #+#             */
/*   Updated: 2024/12/16 12:51:50 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

typedef struct s_coord
{
	int	x;
	int	y;
}	t_coord;

typedef struct s_map
{
	char	**map;
	int		width;
	int		height;
	t_coord	start;
	t_coord	end;
}	t_map;