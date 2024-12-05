/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 10:15:29 by ele-lean          #+#    #+#             */
/*   Updated: 2024/12/05 10:23:38 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	is_update_valid(int *update, t_list *rules)
{
	t_list	*current_rule;
	int		*rule;
	int		pos1;
	int		pos2;

	current_rule = rules;
	while (current_rule)
	{
		rule = (int *)current_rule->content;
		pos1 = get_position(update, rule[0]);
		pos2 = get_position(update, rule[1]);
		if (pos1 != -1 && pos2 != -1 && pos1 > pos2)
			return (0);
		current_rule = current_rule->next;
	}
	return (1);
}

void	swap_positions(int *update, int pos1, int pos2)
{
	int	tmp;

	tmp = update[pos1];
	update[pos1] = update[pos2];
	update[pos2] = tmp;
}

void	apply_sort(int *update, int *rule)
{
	int	i;
	int	j;

	i = 0;
	while (update[i] != -1)
	{
		if (update[i] == rule[0])
			break ;
		i++;
	}
	j = 0;
	while (update[j] != -1)
	{
		if (update[j] == rule[1])
			break ;
		j++;
	}
	swap_positions(update, i, j);
}

void	sort_update(int *update, t_list *rules)
{
	t_list	*current_rule;
	int		changed;
	int		*rule;
	int		pos1;
	int		pos2;

	changed = 1;
	while (changed)
	{
		changed = 0;
		current_rule = rules;
		while (current_rule)
		{
			rule = (int *)current_rule->content;
			pos1 = get_position(update, rule[0]);
			pos2 = get_position(update, rule[1]);
			if (pos1 != -1 && pos2 != -1 && pos1 > pos2)
			{
				apply_sort(update, rule);
				changed = 1;
			}
			current_rule = current_rule->next;
		}
	}
}

int	compute_part2(t_list *rules_start, t_list *updates)
{
	t_list	*current_update;
	int		*update;
	int		total;

	total = 0;
	current_update = updates;
	while (current_update)
	{
		update = (int *)current_update->content;
		if (!is_update_valid(update, rules_start))
		{
			sort_update(update, rules_start);
			total += get_middle(update);
		}
		current_update = current_update->next;
	}
	return (total);
}
