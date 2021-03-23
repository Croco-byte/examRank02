#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <stdio.h>

typedef struct	s_list
{
	int	width;
	int	point;
	int	precis;
}		t_list;

int	ft_putstr(char *s)
{
	int i;

	i = 0;
	while (s[i])
	{
		write(1, &s[i], 1);
		i++;
	}
	return (i);
}

int	ft_putnstr(char *s, int size)
{
	int i;

	i = 0;
	while (s[i] && i < size)
	{
		write(1, &s[i], 1);
		i++;
	}
	return (i);
}

int	ft_putnchar(char c, int nb)
{
	int i;

	i = 0;
	while (i < nb)
	{
		write(1, &c, 1);
		i++;
	}
	return (i);
}

int	ft_strlen(char *s)
{
	int i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

int	is_spec(char c)
{
	if (c == 's' || c == 'd' || c == 'x')
		return (1);
	return (0);
}

int	is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

void	init_flags(t_list *flags)
{
	flags->width = 0;
	flags->point = 0;
	flags->precis = 0;
}

void	parse_flags(t_list *flags, const char *str)
{
	int i;

	i = 0;
	while (str[i] && !is_spec(str[i]))
	{
		if (is_digit(str[i]) && flags->point == 0)
			flags->width = (flags->width * 10) + (str[i] - 48);
		if (str[i] == '.' && flags->point == 0)
			flags->point = 1;
		if (is_digit(str[i]) && flags->point == 1)
			flags->precis = (flags->precis * 10) + (str[i] - 48);
		i++;
	}
}

int	get_size(int number)
{
	unsigned int	num;
	int 		size;

	size = 0;
	if (number == 0)
		return (1);
	if (number < 0)
	{
		size++;
		num = number * -1;
	}
	else
		num = number;
	while(num > 0)
	{
		size++;
		num /= 10;
	}
	return (size);
}

char	*get_number(int number, int size)
{
	unsigned int	num;
	char		*result;

	result = malloc((size + 1) * sizeof(char));
	result[size] = '\0';
	size--;
	if (number == 0)
	{
		result[0] = '0';
		return (result);
	}
	if (number < 0)
		num = number * -1;
	else
		num = number;
	while (size > 0)
	{
		result[size] = (num % 10) + 48;
		size--;
		num /= 10;
	}
	if (number < 0)
		result[size] = '-';
	else
		result[size] = (num % 10) + 48;
       return (result);	
}

int	display_d(t_list flags, va_list value)
{
	int	count;
	int	number;
	int	size;
	char	*result;

	count = 0;
	number = va_arg(value, int);
	size = get_size(number);
	result = get_number(number, size);
	if (number == 0 && flags.point == 1 && flags.precis == 0)
	{
		free(result);
		result = "";
	}
	size = ft_strlen(result);
	if (number >= 0)
	{
		if (flags.width > size && flags.precis <= size)
			count += ft_putnchar(' ', flags.width - size);
		if (flags.width > size && flags.precis > size && flags.precis < flags.width)	
			count += ft_putnchar(' ', flags.width - flags.precis);
		if (flags.precis > size)
			count += ft_putnchar('0', flags.precis - size);
		count += ft_putstr(result);
	}
	else
	{
		if (flags.width > size && flags.precis <= size - 1)
			count += ft_putnchar(' ', flags.width - size);
		if (flags.width > size && flags.precis > size - 1 && flags.precis < flags.width - 1)
			count += ft_putnchar(' ', (flags.width - 1) - flags.precis);
		count += ft_putnchar('-', 1);
		if (flags.precis > size - 1)
			count += ft_putnchar('0', flags.precis - (size - 1));
		count += ft_putstr(&result[1]);
	}	
	if (!(number == 0 && flags.point == 1 && flags.precis == 0))
		free(result);
	return (count);
}

int	get_hex_size(unsigned int number)
{
	int	size;

	size = 0;
	if (number == 0)
		return (1);
	while (number)
	{
		size++;
		number /= 16;
	}
	return (size);
}

char	*get_hex_number(unsigned int number, int size)
{
	char	*result;
	char	*base = "0123456789abcdef";

	result = malloc((size + 1) * sizeof(char));
	result[size] = '\0';
	size--;
	if (number == 0)
	{
		result[0] = '0';
		return (result);
	}
	while (size)
	{
		result[size] = base[number % 16];
		number /= 16;
		size--;
	}
	if (size == 0)
		result[size] = base[number % 16];
	return (result);
}

int	display_x(t_list flags, va_list value)
{
	int		count;
	unsigned int	number;
	int		size;
	char		*result;

	count = 0;
	number = va_arg(value, unsigned int);
	size = get_hex_size(number);
	result = get_hex_number(number, size);
	if (number == 0 && flags.point == 1 && flags.precis == 0)
	{
		free(result);
		result = "";
	}
	size = ft_strlen(result);
	if (flags.width > size && flags.precis <= size)
		count += ft_putnchar(' ', flags.width - size);
	if (flags.width > size && flags.precis > size && flags.precis < flags.width)	
		count += ft_putnchar(' ', flags.width - flags.precis);
	if (flags.precis > size)
		count += ft_putnchar('0', flags.precis - size);
	count += ft_putstr(result);
	if (!(number == 0 && flags.point == 1 && flags.precis == 0))
		free(result);
	return (count);
}

int	display_s(t_list flags, va_list value)
{
	int	count;
	int	size;
	char	*result;

	count = 0;
	result = va_arg(value, char *);
	if (!result)
		result = "(null)";
	if (flags.precis == 0 && flags.point == 1)
		result = "";
	size = ft_strlen(result);
	if (flags.width > size && (flags.point == 0 || (flags.point == 1 && flags.precis >= size)))
		count += ft_putnchar(' ', flags.width - size);
	if (flags.point == 1 && flags.precis < size && flags.width > flags.precis)
		count += ft_putnchar(' ', flags.width - flags.precis);
	count += ft_putnstr(result, (flags.precis < size && flags.point == 1) ? flags.precis : size);
	return (count);
}

int	display_var(char type, t_list flags, va_list value)
{
	int count;

	count = 0;
	if (type == 'd')
		count += display_d(flags, value);
	if (type == 'x')
		count += display_x(flags, value);
	if (type == 's')
		count += display_s(flags, value);
	return (count);
}

int	is_complete_format(const char *format)
{
	int	i;

	i = 0;
	while (format[i] && !is_spec(format[i]))
		i++;
	if (!format[i])
		return (0);
	return (1);
}

int	ft_printf(const char *str, ...)
{
	int	i;
	int	count;
	va_list	value;
	t_list	flags;

	i = 0;
	count = 0;
	va_start(value, str);
	while (str[i])
	{
		if (str[i] == '%' && is_complete_format(&str[i]))
		{
			i++;
			init_flags(&flags);
			parse_flags(&flags, &str[i]);
			while (str[i] && !is_spec(str[i]))
				i++;
			count += display_var(str[i], flags, value);
		}
		else
		{
			write(1, &str[i], 1);
			count++;
		}
		i++;
	}
	va_end(value);
	return (count);
}
