/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/26 11:54:38 by sgaudin           #+#    #+#             */
/*   Updated: 2016/08/06 16:04:14 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		init_implement_functions(t_sh *data)
{
	data->imp_func = (char**)malloc(sizeof(char*) * 7);
	data->imp_func[0] = ft_strdup("echo");
	data->imp_func[1] = ft_strdup("cd");
	data->imp_func[2] = ft_strdup("setenv");
	data->imp_func[3] = ft_strdup("unsetenv");
	data->imp_func[4] = ft_strdup("env");
	data->imp_func[5] = ft_strdup("exit");
	data->imp_func[6] = NULL;
}
/*
void		init_null(char ***new_env, int j)
{
	int i;

	i = 0;
	while (i <= j)
	{
		(*new_env)[i] = NULL;
		i++;
	}
	printf("j = %d\n", j);
}
*/
int			init_env(char ***new_env, char **envp, char *var)
{
	FT_INIT(int, i, 0);
	while (envp && envp[i])
		i++;
	FT_INIT(int, var_malloc, i + ((var != NULL) ? 1 : 0) + 1);
	printf("var_malloc = %d\n", var_malloc);
	(*new_env) = (char **)malloc(sizeof(char *) * var_malloc);
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
