/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvirgile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/26 11:46:36 by dvirgile          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2016/08/06 16:27:53 by sgaudin          ###   ########.fr       */
=======
/*   Updated: 2016/07/28 17:04:34 by dvirgile         ###   ########.fr       */
>>>>>>> ca7f1b9024bfd24ce9556606c75084fcd9897388
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		env_format(char *var)
{
	FT_INIT(int, i, ft_strlen(var) - ft_strlen(ft_strchr(var, '=')));
	FT_INIT(int, j, ft_strlen(ft_strchr(var, '=')));
	if (ft_strchr(var, '=') == NULL)
		return (0);
	FT_INIT(char *, name, ft_strnew(i));
	FT_INIT(char *, value, ft_strnew(j));
	name = strncpy(name, var, i);
	value = strncpy(value, var, j);
	FT_MULTI3(i, j, 0);
	if (ft_strchr(value, '='))
		return (0);
	while (name[i])
	{
		if (name[i] < 'A' || name[i] > 'Z')
			if (name[i] != '_')
				return (0);
		i++;
	}
	return (1);
}

int		distrib_functions(char **commands, t_sh *data)
{
	if (!ft_strcmp(commands[0], "cd"))
		shell_cd(commands);
	else if (!ft_strcmp(commands[0], "env"))
		calls(data, commands);
	else if (!ft_strcmp(commands[0], "setenv"))
		calls(data, commands);
	else if (!ft_strcmp(commands[0], "unsetenv"))
		calls(data, commands);
	else if (!ft_strcmp(commands[0], "echo"))
		calls(data, commands);
	else if (!ft_strcmp(commands[0], "exit"))
		exit(EXIT_SUCCESS);
	return (0);
}

int		lsh_launch(char **args, t_sh *data)
{
	FT_INIT(char*, cmd, NULL);
	FT_INIT(char*, tmp, NULL);
	FT_INIT(int, i, 0);
	FT_INIT(char**, bin_directories, data->bin_directories);
	if (!bin_directories)
		return (0);
//	free_env(data->bin_directories);
	data->bin_directories = get_bin_directories(data->env);
	while (bin_directories && bin_directories[i])
	{
		if (!args || !verif_access(bin_directories[i], args[0]))
			return (0);
		cmd = ft_strjoin(bin_directories[i], "/");
		tmp = cmd;
		cmd = ft_strjoin(cmd, args[0]);
		ft_strdel(&tmp);
		printf("cmd=%s,\n", cmd);
		if (execve(cmd, args, data->env) != -1)
		{
			ft_strdel(&cmd);
			return (1);
		}
		ft_strdel(&cmd);
		i++;
	}
	ft_putstr("minishell: command not found: ");
	ft_putendl(args[0]);
	return (0);
}
