/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/26 11:29:38 by sgaudin           #+#    #+#             */
/*   Updated: 2016/07/26 14:36:50 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		check_varname(char *var, char *to_del)
{
	int		i;
	char	*tmp;

	i = 0;
	while (var[i] != '=')
		i++;
	tmp = (char *)malloc(sizeof(char) * i);
	ft_strncpy(tmp, var, i);
	if (!ft_strcmp(tmp, to_del))
		return (1);
	else
		return (0);
}

int		msh_env(t_sh *data)
{
	int		i;

	i = 0;
	if (!data->env)
		return (1);
	printf("msh_env : %p\n", data->env);
	while (data->env[i])
	{
		ft_putendl(data->env[i]);
		i++;
	}
	return (0);
}

int		msh_setenv(t_sh *data, char *new_var)
{
	char **tmp;

	tmp = NULL;
	init_env(&tmp, data->env, new_var);
	free_env(data->env);
	init_env(&(data->env), tmp, NULL);
	return (0);
}

int		msh_unsetenv(t_sh *data, char *to_del)
{
	char	**tmp;
	int		i;

	i = 0;
	to_del = ft_strtoupper(to_del);
	while (data->env[i])
		i++;
	tmp = (char **)malloc(sizeof(char *) * i);
	i = 0;
	while (data->env[i])
	{
		if (data->env[i] && !check_varname(data->env[i], to_del))
			tmp[i] = ft_strdup(data->env[i]);
		i++;
	}
	tmp[i] = NULL;
	free_env(data->env);
	init_env(&(data->env), tmp, NULL);
	free_env(tmp);
	return (0);
}
