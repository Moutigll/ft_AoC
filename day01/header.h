/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 18:50:22 by ele-lean          #+#    #+#             */
/*   Updated: 2024/12/01 19:04:30 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include "libft.h"

void	get_list(t_list **list1, t_list **list2, int fd);
void	free_list(t_list *list);
void	clean_exit(t_list *list1, t_list *list2, int fd);
int		compute_result(t_list *list1, t_list *list2);
int		compute_result2(t_list *list1, t_list *list2);