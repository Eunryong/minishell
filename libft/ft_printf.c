/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunrlee <eunrlee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 13:46:51 by eunrlee           #+#    #+#             */
/*   Updated: 2022/12/12 21:42:14 by eunrlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	parse_type(va_list ap, char c)
{
	int	len;

	len = 0;
	if (c == 'c')
		len += ft_putchar(ap);
	else if (c == 's')
		len += ft_putstr(ap);
	else if (c == 'd' || c == 'i')
		len += ft_putnum(ap);
	else if (c == 'u')
		len += ft_putunum(ap);
	else if (c == 'x' || c == 'X')
		len += ft_puthex(ap, c);
	else if (c == 'p')
		len += ft_putaddr(ap);
	else if (c == '%')
		len += ft_putpercent(0);
	return (len);
}

int	ft_istype(char c)
{
	if (c == 'c' || c == 's' || c == 'p' || c == 'u' || c == 'i' || c == 'd'
		|| c == 'x' || c == 'X' || c == '%')
		return (1);
	return (0);
}

int	parse_form(va_list ap, char *format)
{
	int	ret;
	int	temp;

	ret = 0;
	while (*format)
	{
		temp = ret;
		if (*format == '%')
		{
			format++;
			if (!ft_istype(*format))
				return (-1);
			ret += parse_type(ap, *format);
		}
		else
				ret += write(1, format, 1);
		if (temp > ret)
			return (-1);
		format++;
	}
	return (ret);
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	size_t	ret;

	va_start(ap, format);
	ret = parse_form(ap, (char *)format);
	va_end(ap);
	return (ret);
}
