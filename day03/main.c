/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 14:34:22 by ele-lean          #+#    #+#             */
/*   Updated: 2024/12/08 06:56:40 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*get_next_mul(char *str, int mode)
{
	if (!str)
		return (NULL);
	while (str[4] && ft_strncmp(str, "mul", 3))
	{
		if (ft_strncmp(str, "don't()", 7) == 0 && mode == 1)
		{
			while (str[5] && ft_strncmp(str, "do()", 4))
			{
				if (!*str)
					return (NULL);
				str++;
			}
		}
		str++;
	}
	if (!*str)
		return (NULL);
	return (str + 3);
}

int	get_mul(char *str)
{
	int	a;
	int	b;
	int	i;

	if (!str || str[0] != '(')
		return (0);
	a = ft_atoi(str + 1);
	i = 1;
	while (ft_isdigit(str[i]))
		i++;
	if (str[i] != ',')
		return (0);
	i++;
	b = ft_atoi(str + i);
	while (ft_isdigit(str[i]))
		i++;
	if (str[i] != ')')
		return (0);
	return (a * b);
}

int	compute(char *line, int mode)
{
	int	result;

	result = 0;
	while (*line)
	{
		line = get_next_mul(line, mode);
		if (line)
		{
			result += get_mul(line);
			line += 1;
		}
	}
	return (result);
}

char	*read_file_to_string(int fd)
{
	char	*line;
	char	*temp;
	char	*new_line;

	line = ft_strdup("");
	if (!line)
		return (NULL);
	temp = get_next_line(fd);
	while (temp)
	{
		new_line = ft_strjoin(line, temp);
		if (!new_line)
		{
			free(temp);
			free(line);
			return (NULL);
		}
		free(line);
		line = new_line;
		free(temp);
		temp = get_next_line(fd);
	}
	return (line);
}

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("day03/input.txt", O_RDONLY);
	if (fd == -1)
	{
		ft_printf("Error opening file\n");
		return (1);
	}
	line = read_file_to_string(fd);
	if (!line)
	{
		ft_printf("Error reading file to string\n");
		close(fd);
		return (1);
	}
	ft_printf("Result: %d\nResult 2: %d\n", compute(line, 0), compute(line, 1));
	close(fd);
	free(line);
	return (0);
}
