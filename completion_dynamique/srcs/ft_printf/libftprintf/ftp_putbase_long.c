/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftp_putbase_long.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvirgile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/12 19:24:53 by dvirgile          #+#    #+#             */
/*   Updated: 2016/03/12 19:24:53 by dvirgile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int	ftp_putbase_long(uintmax_t n, uint32_t base, uint8_t flag, t_docker *data)
{
	FT_INIT(int, len, 0);
	if (base > 0 && base <= 10)
	{
		if (base == 8 && n != 0 && data->dieze == 1)
			ftp_putchar('0');
		if (n >= base)
			len += ftp_putbase_long((n / base), base, flag, data);
		ft_putchar((n % base) + '0');
		len++;
	}
	else if (base == 16)
	{
		if (n != 0 && data->dieze == 1)
			len += (ftp_putchar('0') + ftp_putchar(flag + 23));
		if (n >= 16)
		{
			len += ftp_putbase_long((n / 16), base, flag, data);
			n %= 16;
		}
		ft_putchar((n % 16) >= 10 ? (n % 10) + flag : (n % 16) + '0');
		len++;
	}
	return (len);
}
