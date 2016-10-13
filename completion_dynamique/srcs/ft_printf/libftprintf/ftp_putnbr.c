/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftp_putnbr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvirgile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/12 19:25:12 by dvirgile          #+#    #+#             */
/*   Updated: 2016/03/12 19:25:15 by dvirgile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int		ftp_putnbr(int64_t n, t_docker *data)
{
	if (n < -9223372036854775807)
		return (ftp_putstr((uint8_t *)"9223372036854775808"));
	if (data->space == 1 && data->more == 0
		&& data->precision <= longueur_nb(n) && n > 0)
	{
		data->len += ftp_putchar(' ');
		data->space = 0;
	}
	if (n >= 0 && data->more == 1)
	{
		data->len += 1;
		MULTI(data->more, data->space, 0);
	}
	if (n < 0)
	{
		MULTI(data->more, data->space, 0);
		n = -n;
	}
	if (n >= 10)
		ftp_putnbr((n / 10), data);
	ftp_putchar((n % 10) + '0');
	return (0);
}
