/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 23:06:29 by ele-lean          #+#    #+#             */
/*   Updated: 2024/12/07 03:21:37 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	process_block(t_visited_params *params, t_coord *coord)
{
	t_list	*temp;
	int		y;
	int		x;

	y = coord->y;
	x = coord->x;
	params->map[y][x] = '#';
	temp = compute_path(params->map, 1);
	if (!temp)
		(*params->loop_count)++;
	free_list(temp);
	params->map[y][x] = '.';
	(*params->total_tested)++;
}

void	process_visited_blocks(t_visited_params *params)
{
	t_coord	*coord;
	t_list	*temp;

	while (*params->co_visited != NULL)
	{
		coord = (t_coord *)(*params->co_visited)->content;
		process_block(params, coord);
		system("clear");
		printf("Blocks tested: %d/%d(+1) (%.2f%%) %d\n",
			*params->total_tested, params->total_blocks,
			(float)(*params->total_tested)
			/ params->total_blocks * 100, *params->loop_count);
		temp = *params->co_visited;
		*params->co_visited = (*params->co_visited)->next;
		free(temp->content);
		free(temp);
	}
}

void	compute_loop(char **map)
{
	t_list				*co_visited;
	t_list				*temp;
	int					loop_count;
	int					total_tested;
	t_visited_params	params;

	co_visited = compute_path(map, 0);
	loop_count = 0;
	total_tested = 0;
	temp = co_visited;
	co_visited = co_visited->next;
	free(temp->content);
	free(temp);
	params.co_visited = &co_visited;
	params.map = map;
	params.loop_count = &loop_count;
	params.total_tested = &total_tested;
	params.count_temp = co_visited;
	params.total_blocks = 0;
	while (params.count_temp != NULL)
	{
		params.total_blocks++;
		params.count_temp = params.count_temp->next;
	}
	process_visited_blocks(&params);
}
