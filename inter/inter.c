/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 15:10:09 by user42            #+#    #+#             */
/*   Updated: 2021/01/13 15:45:26 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int		is_in_str(char *str, char c)
{
	int	i;

	i = 0;
	while(str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

void	add_treated_char(char *treated_chars, char c)
{
	int	i;

	i = 0;
	while (treated_chars[i])
		i++;
	treated_chars[i] = c;
	treated_chars[i + 1] = '\0';
}

int		main(int argc, char **argv)
{
	int		i;
	int		j;
	char	treated_chars[127];

	i = 0;
	treated_chars[0] = '\0';
	if (argc != 3)
	{
		write(1, "\n", 1);
		return (1);
	}

	while (argv[1][i])
	{
		j = 0;
		while (argv[2][j])
		{
			if (argv[1][i] == argv[2][j] && !is_in_str(treated_chars, argv[1][i]))
			{
				write(1, &argv[1][i], 1);
				add_treated_char(treated_chars, argv[1][i]);
			}
			j++;
		}
		i++;
	}
	write(1, "\n", 1);
	return (0);
}
