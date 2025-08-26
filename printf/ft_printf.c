/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaletham <oaletham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 14:08:44 by oaletham          #+#    #+#             */
/*   Updated: 2025/08/26 20:40:38 by oaletham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdio.h>

int	ft_print_char(char c);
int	ft_print_string(const char *s);
int	ft_print_nbr(int n);


static int	handle(char c, va_list ar)
{
	if (c == 'c')
		return (ft_print_char((char)va_arg(ar, int)));
	if (c == 's')
		return (ft_print_string(va_arg(ar, char *)));
	if (c == 'i' || c == 'd')
		return (ft_print_nbr(va_arg(ar, int)));
	return (0);
}

int	ft_printf(const char *arg, ...)
{
	va_list	ar;
	int		i;
	int		ch;
	int		printed;

	if (!arg)
		return (0);
	i = 0;
	if (!arg)
		return (0);
	va_start(ar, arg);
	while (arg[i])
	{
		if (arg[i] == '%' && arg[i + 1])
		{
			printed += handle(arg[i + 1], ar);
			i = i + 2;
		}
		else
			printed += ft_print_char(arg[i++]);
		va_end(ar);
	}
	return (printed);
}

int	main(void)
{
	int	c;
	int	s;

	c = ft_printf("my age iss  %i\n", -2147483648);
	s = printf("my age iss  %ld\n", -2147483648);
	printf("%i\n", c);
	printf("%i\n", s);
}
