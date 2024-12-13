/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 11:12:00 by ele-lean          #+#    #+#             */
/*   Updated: 2024/12/13 14:35:53 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stdio.h>
#include "libft.h"

typedef struct s_machine
{
	int		ax;
	int		ay;
	int		bx;
	int		by;
	long	px;
	long	py;
}	t_machine;