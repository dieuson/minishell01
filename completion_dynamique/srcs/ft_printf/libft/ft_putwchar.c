/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putwchar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvirgile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/14 14:35:46 by dvirgile          #+#    #+#             */
/*   Updated: 2016/03/14 15:15:23 by dvirgile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"
#include "../libftprintf/libftprintf.h"

#define MASK_2 "110xxxxx 10xxxxxx"
#define MASK_3 "1110xxxx 10xxxxxx 10xxxxxx"
#define MASK_4 "11110xxx 10xxxxxx 10xxxxxx 10xxxxxx"

static void		ft_memdel_tab(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
	{
		ft_memdel((void *)&tab[i]);
		i++;
	}
}

static char		**set_mask(char *bin_value, char *mask_macro)
{
	char	*mask;
	int		size;
	int		bin_size;
	int		i;

	mask = ft_strdup(mask_macro);
	size = ft_strlen(mask) - 1;
	bin_size = ft_strlen(bin_value) - 1;
	while (size >= 0 && bin_size >= 0)
	{
		if (mask[size] == 'x')
		{
			mask[size] = bin_value[bin_size];
			bin_size--;
		}
		size--;
	}
	i = 0;
	while (mask[i])
	{
		if (mask[i] == 'x')
			mask[i] = '0';
		i++;
	}
	return (ft_strsplit(mask, ' '));
}

int				ft_putwchar(wchar_t c, int count)
{
	char	**final;

	FT_INIT(char *, bin_value, ft_strnew(33));
	FT_INIT(int, i, 0);
	FT_INIT(int, octet, 0);
	bin_value = ft_itoa_base((int)c, 2);
	if (ft_strlen(bin_value) <= 7)
		return (ftp_putchar((char)c));
	else if (ft_strlen(bin_value) <= 11)
		final = set_mask(bin_value, MASK_2);
	else if (ft_strlen(bin_value) > 11 && ft_strlen(bin_value) <= 16)
		final = set_mask(bin_value, MASK_3);
	else
		final = set_mask(bin_value, MASK_4);
	ft_memdel((void **)&bin_value);
	while (final[i])
	{
		octet = ft_atoibase(final[i], 2);
		if (count == 0)
			write(1, &octet, 1);
		i++;
	}
	ft_memdel_tab(final);
	return (i);
}
