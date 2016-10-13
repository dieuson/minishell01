/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_capitalize.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvirgile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/12 18:51:10 by dvirgile          #+#    #+#             */
/*   Updated: 2016/03/12 18:51:13 by dvirgile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	ft_capitalize(char *str)
{
	int i;

	i = 0;
	str = ft_strtolower(str);
	if (str[0] >= 'a' && str[0] <= 'z')
		str[0] -= 32;
	while (str[i] != '\0')
	{
		if ((str[i - 1] >= 32 && str[i - 1] <= 38)
			|| (str[i - 1] >= 40 && str[i - 1] <= 44)
			|| (str[i - 1] >= 46 && str[i - 1] <= 47)
			|| (str[i - 1] >= 58 && str[i - 1] <= 64)
			|| (str[i - 1] >= 91 && str[i - 1] <= 96)
			|| (str[i - 1] >= 123 && str[i - 1] <= 126))
		{
			if (str[i] >= 'a' && str[i] <= 'z')
				str[i] -= 32;
		}
		ft_putchar(str[i]);
		i++;
	}
}
