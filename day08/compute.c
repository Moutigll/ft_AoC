/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 07:26:24 by ele-lean          #+#    #+#             */
/*   Updated: 2024/12/08 10:28:04 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	find_antinodes(char **map,
		t_antinode antinode, int height, t_list **antinodes_list)
{
	t_coords	c;

	c.width = ft_strlen(map[0]);
	c.y = 0;
	while (c.y < height)
	{
		c.x = 0;
		while (map[c.y][c.x])
		{
			if (map[antinode.y][antinode.x] == map[c.y][c.x]
			&& (antinode.x != c.x || antinode.y != c.y))
			{
				c.dx = c.x - antinode.x;
				c.dy = c.y - antinode.y;
				add_antinode(antinodes_list,
					(t_antinode){antinode.x - c.dx, antinode.y - c.dy},
					c.width, height);
				add_antinode(antinodes_list,
					(t_antinode){c.x + c.dx, c.y + c.dy}, c.width, height);
			}
			c.x++;
		}
		c.y++;
	}
}

void	calculate_antinodes(t_antinode antinode, t_coords *c,
		t_list **antinodes_list)
{
	int	ax;
	int	ay;
	int	bx;
	int	by;

	ax = antinode.x;
	ay = antinode.y;
	while (ax >= 0 && ax < c->width && ay >= 0 && ay < c->height)
	{
		if (!(ax == antinode.x && ay == antinode.y))
			add_antinode(antinodes_list,
				(t_antinode){ax, ay}, c->width, c->height);
		ax += c->dx;
		ay += c->dy;
	}
	bx = c->x;
	by = c->y;
	while (bx >= 0 && bx < c->width && by >= 0 && by < c->height)
	{
		if (!(bx == c->x && by == c->y))
			add_antinode(antinodes_list,
				(t_antinode){bx, by}, c->width, c->height);
		bx -= c->dx;
		by -= c->dy;
	}
}

void	find_antinodes2(char **map,
	t_antinode antinode, int height, t_list **antinodes_list)
{
	t_coords	c;

	c.width = ft_strlen(map[0]);
	c.height = height;
	c.y = 0;
	while (c.y < height)
	{
		c.x = 0;
		while (map[c.y][c.x])
		{
			if (map[antinode.y][antinode.x] == map[c.y][c.x]
				&& (antinode.x != c.x || antinode.y != c.y))
			{
				c.dx = c.x - antinode.x;
				c.dy = c.y - antinode.y;
				calculate_antinodes(antinode, &c, antinodes_list);
			}
			c.x++;
		}
		c.y++;
	}
}

void	draw_antinodes(char **map, t_list *antinodes_list)
{
	t_antinode	*antinode;
	int			i;
	int			j;

	i = 0;
	while (antinodes_list)
	{
		antinode = (t_antinode *)antinodes_list->content;
		if (map[antinode->y][antinode->x] == '.'
			|| ft_isalpha(map[antinode->y][antinode->x])
			|| ft_isdigit(map[antinode->y][antinode->x]))
		{
			i++;
			map[antinode->y][antinode->x] = '#';
		}
		antinodes_list = antinodes_list->next;
	}
	j = 0;
	while (map[j])
	{
		ft_printf("%s", map[j]);
		j++;
	}
	printf("Antinodes found: %d\n\n", i);
}

void	compute(char **map, int height, int mode)
{
	int		x;
	int		y;
	t_list	*an_list;

	an_list = NULL;
	y = 0;
	while (y < height)
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] != '.')
			{
				if (mode == 0)
					find_antinodes(map, (t_antinode){x, y}, height, &an_list);
				else
					find_antinodes2(map, (t_antinode){x, y}, height, &an_list);
			}
			x++;
		}
		y++;
	}
	draw_antinodes(map, an_list);
	ft_lstclear(&an_list, free_antinode);
}
