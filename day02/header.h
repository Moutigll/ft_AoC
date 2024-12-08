/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 14:34:41 by ele-lean          #+#    #+#             */
/*   Updated: 2024/12/08 06:56:46 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "libft.h"

void	get_list(t_list **list, int fd);
int		check_values(int value1, int value2, int order);
int		has_duplicates(char **list);
int		is_sorted(char **list);
int		len(char **list);
char	**get_content(char **list, int size);
void	free_list_element(void *ptr);