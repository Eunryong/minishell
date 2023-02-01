/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printnum.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunrlee <eunrlee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 23:43:56 by eunrlee           #+#    #+#             */
/*   Updated: 2022/12/12 21:42:36 by eunrlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putunum(va_list ap)
{
	unsigned int	num;
	char			*s;
	size_t			len;
	size_t			s_len;

	len = 0;
	num = va_arg(ap, unsigned int);
	s = ft_itoa(num);
	if (!s)
		return (-1);
	s_len = ft_strlen(s);
	if (write(1, s, s_len) < 0)
	{
		free(s);
		return (-1);
	}
	len += s_len;
	free(s);
	return (len);
}

int	ft_hexlen(size_t num)
{
	int	len;

	len = 0;
	while (num > 0)
	{
		len++;
		num /= 16;
	}
	return (len);
}

char	*ft_makehex(size_t num, char *hex)
{
	char	*ret;
	size_t	ret_len;

	if (num == 0)
		return (ft_strdup("0"));
	ret_len = ft_hexlen(num);
	ret = (char *)malloc(sizeof(char) * ret_len + 1);
	if (!ret)
		return (0);
	ret [ret_len] = 0;
	while (num)
	{
		ret[--ret_len] = hex[num % 16];
		num /= 16;
	}
	return (ret);
}

int	ft_puthex(va_list ap, char c)
{
	char	*hex;
	size_t	num;
	size_t	len;
	char	*s;
	size_t	s_len;

	len = 0;
	if (c == 'x')
		hex = "0123456789abcdef";
	else
		hex = "0123456789ABCDEF";
	num = va_arg(ap, unsigned int);
	s = ft_makehex(num, hex);
	if (!s)
		return (-1);
	s_len = ft_strlen(s);
	if (write(1, s, s_len) < 0)
	{
		free(s);
		return (-1);
	}
	len += s_len;
	free(s);
	return (len);
}

int	ft_putnum(va_list ap)
{
	int			num;
	char		*s;
	size_t		len;
	size_t		s_len;

	len = 0;
	num = va_arg(ap, int);
	s = ft_itoa(num);
	if (!s)
		return (-1);
	s_len = ft_strlen(s);
	if (write(1, s, s_len) < 0)
	{
		free(s);
		return (-1);
	}
	len += s_len;
	free(s);
	return (len);
}
