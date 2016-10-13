/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_putchar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvirgile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/12 19:19:36 by dvirgile          #+#    #+#             */
/*   Updated: 2016/03/12 19:19:36 by dvirgile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

int		ftp_distrib_char(t_docker *data, int32_t str, int len, int who)
{
	if (who == -1)
	{
		len += ftp_putchar(str);
		return (len = ft_add_spaces((data->width - 1), len,
		data->zero == 1 ? '0' : ' '));
	}
	else if (who == 3)
		len = ft_add_spaces((data->width - 1), len,
		data->zero == 1 || data->dot ? '0' : ' ');
	return (len += ftp_putchar(str));
}

int		call_putchar(const char *str, va_list args, t_docker *data)
{
	int32_t	argument;

	if (data->length == l)
		return (ft_putwchar(va_arg(args, wint_t), 0));
	else
		argument = va_arg(args, uint32_t);
	if (data->width >= 1 && data->less == 0)
		data->len = ftp_distrib_char(data, argument, data->len, 3);
	else if (data->less == 1 && str)
		data->len = ftp_distrib_char(data, argument, data->len, -1);
	else
		data->len = ftp_distrib_char(data, argument, data->len, 4);
	return (0);
}
