#include <stdio.h>

int	ft_printf(const char *str, ...);

int	main(void)
{
	ft_printf("|%3.1s|\n", NULL);
	printf("|%3.1s|\n", NULL);
	return (0);
}
