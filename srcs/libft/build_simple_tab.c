/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_simple_tab.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvirgile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/06 11:58:26 by dvirgile          #+#    #+#             */
/*   Updated: 2016/06/06 12:00:07 by dvirgile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/libft.h"

void		free_simple_tab(char ***tab)
{
	int		colonne;

	colonne = 0;
	while ((*tab) && (*tab)[colonne])
	{
		free((*tab)[colonne]);
		(*tab)[colonne] = NULL;
		colonne++;
	}
	free(*tab);
	*tab = NULL;
}

char		**copy_simple_tab(char **src, char **dest)
{
	int		colonne;

	colonne = 0;
	while (src && src[colonne])
	{
		dest[colonne] = ft_strdup(src[colonne]);
		colonne++;
	}
	dest[colonne] = NULL;
	return (dest);
}

char		**new_simple_tab(char ***tab)
{
	char	**fraiche_tab;
	int		colonne;

	colonne = 0;
	if (!tab || !(*tab))
		return (fraiche_tab = (char **)malloc(sizeof(char *) * 2));
	while (*tab && (*tab)[colonne])
		colonne++;
	fraiche_tab = (char **)malloc(sizeof(char *) * (colonne + 2));
	fraiche_tab = copy_simple_tab(*tab, fraiche_tab);
	free_simple_tab(&(*tab));
	return (fraiche_tab);
}
