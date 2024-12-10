/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 06:10:14 by ele-lean          #+#    #+#             */
/*   Updated: 2024/12/10 08:41:58 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "libft.h"
#include <stdio.h>

long int	get_checksum(int ***tab, int size);
void		free_disk(int ***tab, int size);
int			***gen_tab(char *disk, int size);
