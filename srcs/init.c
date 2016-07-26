/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/26 11:54:38 by sgaudin           #+#    #+#             */
/*   Updated: 2016/07/26 12:05:18 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_minishell(t_sh *data, char **envp)
{
	int		i;

	data->env = NULL;
	i = 0;
	while (envp[i])
		i++;
	data->env = (char **)malloc(sizeof(char *) * i + 1);
	i = 0;
	while (envp[i])
	{
		data->env[i] = ft_strdup(envp[i]);
		i++;
	}
	data->env[i] = NULL;
}
