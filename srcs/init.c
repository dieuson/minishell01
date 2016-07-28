/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/26 11:54:38 by sgaudin           #+#    #+#             */
/*   Updated: 2016/07/28 15:16:58 by sgaudin          ###   ########.fr       */
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
	printf("envp[i] = %s\n", envp[i]);
	while (envp && envp[i])
		i++;
	(*new_env) = (char **)malloc(sizeof(char *) * i + ((var != NULL) ? 1 : 0));
	if (!(*new_env))
		return (1);
//	init_null(new_env, i + (var != NULL ? 1 : 0));
	i = 0;
	while (envp[i])
	{
		(*new_env)[i] = ft_strdup(envp[i]);
		i++;
	}
	printf("(*new_env)[0] = %s\n", (*new_env)[0]);
	if (var != NULL)
	{
		printf("var = %s, i = %d\n", var, i);
		printf("(*new_env)[0] = %s\n", (*new_env)[0]);
		(*new_env)[i] = ft_strdup(var);
		printf("coucou %s\n", (*new_env)[i]);
		i++;
	}
	printf("(*new_env)[0] = %s, new_env[i - 1] = %s\n", (*new_env)[0], (*new_env)[i - 1]);
	(*new_env)[i] = NULL;
	printf("(*new_env)[0] = %s, new_env[i] = %s, new_env[i - 1] = %s\n", (*new_env)[0], (*new_env)[i], (*new_env)[i - 1]);
	return (0);
}
