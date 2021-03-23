#include "get_next_line.h"
#include <stdio.h>

int	main(void)
{
	int	reader;
	char	*line;

	line = 0;
	while ((reader = get_next_line(&line)) > 0)
	{
		printf("%s\n", line);
		free(line);
	}
	printf("%s", line);
	free(line);
}
