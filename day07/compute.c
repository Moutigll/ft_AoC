/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 18:13:41 by ele-lean          #+#    #+#             */
/*   Updated: 2024/12/07 22:56:06 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

long int	concat_long_int(long int num1, long int num2)
{
	long int	factor;

	factor = 1;
	while (factor <= num2)
		factor *= 10;
	return (num1 * factor + num2);
}

long int	process_combinations(t_combination *comb, int mode)
{
	t_combination_vars	vars;

	vars.new_comb_add = *comb;
	vars.new_comb_add.current_value += comb->tab[comb->index];
	vars.new_comb_add.index += 1;
	vars.result_add = find_combination(&vars.new_comb_add, mode);
	if (vars.result_add != 0)
		return (vars.result_add);
	vars.new_comb_mul = *comb;
	vars.new_comb_mul.current_value *= comb->tab[comb->index];
	vars.new_comb_mul.index += 1;
	vars.result_mul = find_combination(&vars.new_comb_mul, mode);
	if (vars.result_mul != 0)
		return (vars.result_mul);
	if (mode == 1)
	{
		vars.new_comb_concat = *comb;
		vars.new_comb_concat.current_value
			= concat_long_int(comb->current_value, comb->tab[comb->index]);
		vars.new_comb_concat.index += 1;
		vars.result_concat = find_combination(&vars.new_comb_concat, mode);
		if (vars.result_concat != 0)
			return (vars.result_concat);
	}
	return (0);
}

long int	find_combination(t_combination *comb, int mode)
{
	if (comb->index >= comb->size)
	{
		if (comb->current_value == comb->target)
			return (comb->target);
		return (0);
	}
	return (process_combinations(comb, mode));
}

long int	search_combinations(long int *tab,
		int size, long int target, int mode)
{
	t_combination	comb;

	comb.tab = tab;
	comb.size = size;
	comb.target = target;
	comb.current_value = tab[0];
	comb.index = 1;
	return (find_combination(&comb, mode));
}

long int	compute(t_list *list, int mode)
{
	long int	*tab;
	long int	result;
	long int	total;

	total = 0;
	while (list)
	{
		tab = (long int *)list->content;
		result = tab[0];
		total += search_combinations(tab + 1, ft_tablen((void **)tab) - 1,
				result, mode);
		list = list->next;
	}
	return (total);
}
