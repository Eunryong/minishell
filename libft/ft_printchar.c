/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printchar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunrlee <eunrlee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 01:05:29 by eunrlee           #+#    #+#             */
/*   Updated: 2022/12/12 21:42:00 by eunrlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putchar(va_list ap)
{
	int		len;
	char	c;

	len = 0;
	c = (unsigned char)va_arg(ap, int);
	len += write(1, &c, 1);
	if (len != 1)
		return (-1);
	return (len);
}

int	ft_putpercent(int len)
{
	len += write(1, "%", 1);
	if (len != 1)
		return (-1);
	return (len);
}

int	ft_putstr(va_list ap)
{
	size_t		len;
	size_t		s_len;
	char		*s;

	len = 0;
	s = va_arg(ap, char *);
	if (!s)
	{
		if (write(1, "(null)", 6) < 0)
			return (-1);
		len += 6;
		return (len);
	}
	s_len = ft_strlen(s);
	if (write(1, s, s_len) < 0)
		return (-1);
	len += s_len;
	return (len);
}
