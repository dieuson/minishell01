/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/26 12:01:06 by sgaudin           #+#    #+#             */
/*   Updated: 2016/07/26 13:50:57 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		free_env(char **env)
{
	int i;

	i = 0;
	while (env[i])
	{
		if (env[i])
			free(env[i]);
		i++;
	}
	free(env);
}
