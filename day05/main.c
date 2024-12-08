/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 06:28:58 by ele-lean          #+#    #+#             */
/*   Updated: 2024/12/08 06:16:58 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	get_position(int *tab, int n)
{
	int	i;

	i = 0;
	while (tab[i] != -1)
	{
		if (tab[i] == n)
			return (i);
		i++;
	}
	return (-1);
}

int	get_middle(int *tab)
{
	int	i;

	i = 0;
	while (tab[i] != -1)
		i++;
	if (i == 0)
		return (-1);
	return (tab[i / 2]);
}

int	compute_part1(t_list *rules_start, t_list *updates)
{
	t_list	*current_update;
	int		total;
	int		*update;

	total = 0;
	current_update = updates;
	while (current_update)
	{
		update = (int *)current_update->content;
		if (is_update_valid(update, rules_start))
			total += get_middle(update);
		current_update = current_update->next;
	}
	return (total);
}

int	main(void)
{
	t_list	*rules;
	t_list	*updates;

	rules = NULL;
	updates = NULL;
	parse_input(&rules, &updates);
	ft_printf("Part 1: %d\n", compute_part1(rules, updates));
	ft_printf("Part 2: %d\n", compute_part2(rules, updates));
	free_list(rules);
	free_list(updates);
	return (0);
}
