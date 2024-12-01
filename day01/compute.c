/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 20:54:38 by ele-lean          #+#    #+#             */
/*   Updated: 2024/12/01 20:54:48 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	compute_result(t_list *list1, t_list *list2)
{
	int	result;
	int	value;

	result = 0;
	while (list1)
	{
		value = *(int *)list1->content - *(int *)list2->content;
		if (value < 0)
			value *= -1;
		result += value;
		list1 = list1->next;
		list2 = list2->next;
	}
	return (result);
}

int	compute_result2(t_list *list1, t_list *list2)
{
	int		result;
	t_list	*tmp;

	result = 0;
	while (list1)
	{
		tmp = list2;
		while (tmp)
		{
			if (*(int *)list1->content == *(int *)tmp->content)
				result += *(int *)list1->content;
			tmp = tmp->next;
		}
		list1 = list1->next;
	}
	return (result);
}
