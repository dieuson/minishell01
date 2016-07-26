/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/26 11:54:38 by sgaudin           #+#    #+#             */
/*   Updated: 2016/07/26 14:38:51 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		init_env(char ***new_env, char **envp, char *var)
{
	int		i;

	i = 0;
	while (envp[i])
		i++;
	(*new_env) = (char **)malloc(sizeof(char *) * i + 1 + (var != NULL ? 1 : 0));
	if (!(*new_env))
		return (1);
	i = 0;
	while (envp[i])
	{
		(*new_env)[i] = ft_strdup(envp[i]);
		i++;
	}
	if (var != NULL)
	{
		(*new_env)[i] = ft_strdup(var);
		i++;
	}
	(*new_env)[i] = NULL;
	return (0);
}
