/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printmem.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunrlee <eunrlee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 20:31:27 by eunrlee           #+#    #+#             */
/*   Updated: 2022/12/12 21:42:25 by eunrlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putaddr(va_list ap)
{
	size_t	addr;
	char	*hex;
	char	*s;
	size_t	len;
	size_t	s_len;

	len = 0;
	addr = va_arg(ap, size_t);
	if (write(1, "0x", 2) < 0)
		return (-1);
	len += 2;
	hex = "0123456789abcdef";
	s = ft_makehex(addr, hex);
	if (!s)
		return (-1);
	s_len = ft_strlen(s);
	if (write(1, s, s_len) < 0)
		return (-1);
	len += s_len;
	free(s);
	return (len);
}
