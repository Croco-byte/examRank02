/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   union.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 15:58:50 by user42            #+#    #+#             */
/*   Updated: 2021/01/13 16:26:23 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int		char_encountered(char *str, char c, int index)
{
	int	i;

	i = 0;
	while (i < index)
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int		char_in_string(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int		main(int argc, char **argv)
{
	int	i;

	i = 0;
	if (argc != 3)
	{
		write(1, "\n", 1);
		return (1);
	}
	while (argv[1][i])
	{
		if (!char_encountered(argv[1], argv[1][i], i))
			write(1, &argv[1][i], 1);
		i++;
	}
	i = 0;
	while (argv[2][i])
	{
		if (!char_encountered(argv[2], argv[2][i], i) && !char_in_string(argv[1], argv[2][i]))
			write(1, &argv[2][i], 1);
		i++;
	}
	write(1, "\n", 1);
	return (0);
}
