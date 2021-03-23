/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 15:43:58 by user42            #+#    #+#             */
/*   Updated: 2021/01/13 15:50:16 by user42           ###   ########.fr       */
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

int		main(int argc, char **argv)
{
	int	i;
	int	j;

	i = 0;
	if (argc != 3)
	{
		write(1, "\n", 1);
		return (1);
	}
	while (argv[1][i])
	{
		if (!char_encountered(argv[1], argv[1][i], i))
		{
			j = 0;
			while (argv[2][j])
			{
				if (argv[1][i] == argv[2][j])
				{
					write(1, &argv[1][i], 1);
					break ;
				}
				j++;
			}
		}
		i++;
	}
	write(1, "\n", 1);
	return (0);
}
