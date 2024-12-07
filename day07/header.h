/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 16:53:05 by ele-lean          #+#    #+#             */
/*   Updated: 2024/12/07 22:51:44 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stdio.h>
#include <fcntl.h>
#include "libft.h"

typedef struct s_combination
{
	long int	*tab;
	int			size;
	long int	target;
	long int	current_value;
	int			index;
}	t_combination;

typedef struct s_combination_vars
{
	long int		result_add;
	long int		result_mul;
	long int		result_concat;
	t_combination	new_comb_add;
	t_combination	new_comb_mul;
	t_combination	new_comb_concat;
}	t_combination_vars;

long int	compute(t_list *list, int mode);
long int	find_combination(t_combination *comb, int mode);