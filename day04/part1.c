/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 07:29:57 by ele-lean          #+#    #+#             */
/*   Updated: 2024/12/04 07:56:58 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	init_directions(t_direction directions[8])
{
	directions[0].di = 0;
	directions[0].dj = 1;
	directions[1].di = 1;
	directions[1].dj = 0;
	directions[2].di = 1;
	directions[2].dj = 1;
	directions[3].di = 1;
	directions[3].dj = -1;
	directions[4].di = 0;
	directions[4].dj = -1;
	directions[5].di = -1;
	directions[5].dj = 0;
	directions[6].di = -1;
	directions[6].dj = -1;
	directions[7].di = -1;
	directions[7].dj = 1;
}

// Fonction pour vérifier si "XMAS" est trouvé dans une direction donnée
int	find_xmas_in_direction(t_grid grid_info, int i, int j, t_direction dir)
{
	int	k;
	int	ni;
	int	nj;

	k = 0;
	while (k < WORD_LEN)
	{
		ni = i + k * dir.di;
		nj = j + k * dir.dj;
		if (ni < 0 || ni >= grid_info.rows || nj < 0
			|| nj >= grid_info.cols || grid_info.grid[ni][nj] != WORD[k])
		{
			return (0);
		}
		k++;
	}
	return (1);
}

int	process_cell(t_grid grid_info, int i, int j, t_direction directions[8])
{
	int	d;
	int	count;

	count = 0;
	d = 0;
	while (d < 8)
	{
		if (find_xmas_in_direction(grid_info, i, j, directions[d]))
		{
			count++;
		}
		d++;
	}
	return (count);
}

// Fonction pour compter toutes les occurrences de "XMAS"
int	count_xmas(char **grid, int rows, int cols)
{
	int			count;
	int			i;
	int			j;
	t_direction	directions[8];
	t_grid		grid_info;

	grid_info.grid = grid;
	grid_info.rows = rows;
	grid_info.cols = cols;
	init_directions(directions);
	count = 0;
	i = 0;
	while (i < rows)
	{
		j = 0;
		while (j < cols)
		{
			count += process_cell(grid_info, i, j, directions);
			j++;
		}
		i++;
	}
	return (count);
}
