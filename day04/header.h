/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 06:20:55 by ele-lean          #+#    #+#             */
/*   Updated: 2024/12/08 06:56:31 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "libft.h"

#define WORD "XMAS"
#define WORD_LEN 4

typedef struct s_direction
{
	int	di;
	int	dj;
}	t_direction;

typedef struct s_grid
{
	char	**grid;
	int		rows;
	int		cols;
}	t_grid;

int	count_xmas(char **grid, int rows, int cols);