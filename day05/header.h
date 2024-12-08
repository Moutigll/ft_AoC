/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 06:29:12 by ele-lean          #+#    #+#             */
/*   Updated: 2024/12/08 06:56:26 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft.h"

void	parse_input(t_list **rules, t_list **updates);
int		is_update_valid(int *update, t_list *rules);
int		compute_part2(t_list *rules_start, t_list *updates);
int		get_position(int *tab, int n);
int		get_middle(int *tab);