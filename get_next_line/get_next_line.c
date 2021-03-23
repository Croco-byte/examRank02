#include "get_next_line.h"

int	ft_strlen(char *str)
{
	int i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

int	has_return(char *save)
{
	int i;

	i = 0;
	if (!save)
		return (0);
	while (save[i])
	{
		if (save[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strjoin(char *save, char* buffer)
{
	char	*result;
	int	i;
	int	j;
	int	save_size;
	int	buffer_size;

	i = 0;
	j = 0;
	save_size = ft_strlen(save);
	buffer_size = ft_strlen(buffer);
	if (!save && !buffer)
		return (0);
	if (!(result = malloc((save_size + buffer_size + 1) * sizeof(char))))
		return (0);
	while (i < save_size)
	{
		result[i] = save[i];
		i++;
	}
	while (j < buffer_size)
	{
		result[i + j] = buffer[j];
		j++;
	}
	result[i + j] = '\0';
	free(save);
	return (result);
}

char	*line_from_save(char *save)
{
	char	*result;
	int 	i;

	i = 0;
	if (!save)
		return (0);
	while (save[i] && save[i] != '\n')
		i++;
	if(!(result = malloc((i + 1) * sizeof(char))))
		return (0);
	i = 0;
	while (save[i] && save[i] != '\n')
	{
		result[i] = save[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

char	*update_save(char *save)
{
	char	*new_save;
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!save)
		return (0);
	while (save[i] && save[i] != '\n')
		i++;
	if (save[i] == '\0')
	{
		free(save);
		return (0);
	}
	if (!(new_save = malloc((ft_strlen(save) - i + 1) * sizeof(char))))
		return (0);
	i++;
	while (save[i])
		new_save[j++] = save[i++];
	new_save[j] = '\0';
	free(save);
	return (new_save);
}

int	get_next_line(char **line)
{
	char		buffer[BUFF_SIZE + 1];
	static char	*save = 0;
	int		reader;

	reader = 1;
	if (!line || BUFF_SIZE <= 0)
		return (-1);
	while (!has_return(save) && reader != 0)
	{
		if ((reader = read(0, buffer, BUFF_SIZE)) == -1)
			return (-1);
		buffer[reader] = '\0';
		save = ft_strjoin(save, buffer);
	}
	*line = line_from_save(save);
	save = update_save(save);
	if (reader == 0)
		return (0);
	return (1);
}
