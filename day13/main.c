/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 11:11:42 by ele-lean          #+#    #+#             */
/*   Updated: 2024/12/13 14:40:33 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

#define MAX_PRESSES 100

long int	calculate_min_cost(t_machine machine, long int offset)
{
	long int	n;
	long int	m;
	long int	cost;
	long int	prize_x;
	long int	prize_y;

	prize_x = machine.px + offset;
	prize_y = machine.py + offset;
	if (machine.ax * machine.by - machine.bx * machine.ay == 0)
		return (0);
	n = (prize_x * machine.by - prize_y * machine.bx)
		/ (machine.ax * machine.by - machine.bx * machine.ay);
	m = (machine.ax * prize_y - prize_x * machine.ay)
		/ (machine.ax * machine.by - machine.bx * machine.ay);
	if ((machine.ax * n + machine.bx * m) == prize_x
		&& (machine.ay * n + machine.by * m) == prize_y)
	{
		cost = 3 * n + m;
		if (cost < 0)
			return (0);
		return (cost);
	}
	return (0);
}

void	get_machine(int fd, int i, t_machine *machines)
{
	char	*line;

	line = get_next_line(fd);
	if (!line || !ft_strchr(line, 'X'))
		return (free(line), free(machines));
	machines[i].ax = ft_atoi(ft_strchr(line, 'X') + 1);
	machines[i].ay = ft_atoi(ft_strchr(line, 'Y') + 1);
	free(line);
	line = get_next_line(fd);
	if (!line || !ft_strchr(line, 'X'))
		return (free(line), free(machines));
	machines[i].bx = ft_atoi(ft_strchr(line, 'X') + 1);
	machines[i].by = ft_atoi(ft_strchr(line, 'Y') + 1);
	free(line);
	line = get_next_line(fd);
	if (!line || !ft_strchr(line, '='))
		return (free(line), free(machines));
	machines[i].px = ft_atoi(ft_strchr(line, '=') + 1);
	machines[i].py = ft_atoi(ft_strchr(ft_strchr(line, '=') + 1, '=') + 1);
	free(line);
	line = get_next_line(fd);
	free(line);
}

t_machine	*get_machines(void)
{
	int			fd;
	int			height;
	t_machine	*machines;
	int			i;

	fd = open("day13/input.txt", O_RDONLY);
	if (fd == -1)
		return (NULL);
	height = ft_getnline("day13/input.txt") + 1;
	if ((height) % 4 != 0)
		return ((ft_printf("Error: File format is invalid. Lines: %d\n",
					height)), NULL);
	machines = malloc(sizeof(t_machine) * (height / 4));
	if (!machines)
		return (NULL);
	i = 0;
	while (i < height / 4)
	{
		get_machine(fd, i, machines);
		i++;
	}
	close(fd);
	return (machines);
}

int	main(void)
{
	t_machine	*machines;
	int			num_machines;
	int			i;
	long int	part1;
	long int	part2;

	machines = get_machines();
	if (!machines)
	{
		ft_printf("Error reading machines.\n");
		return (1);
	}
	num_machines = ft_getnline("day13/input.txt") / 4 + 1;
	i = 0;
	part1 = 0;
	part2 = 0;
	while (i < num_machines)
	{
		part1 += calculate_min_cost(machines[i], 0);
		part2 += calculate_min_cost(machines[i], 10000000000000);
		i++;
	}
	printf("Part 1: %ld\nPart 2: %ld\n", part1, part2);
	free(machines);
	return (0);
}
