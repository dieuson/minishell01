/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvirgile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/26 11:46:36 by dvirgile          #+#    #+#             */
/*   Updated: 2016/08/06 16:17:46 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		env_format(char *var)
{
	if (ft_strchr(var, '=') == NULL)
		return (0);
	FT_INIT(int, i, ft_strlen(var) - ft_strlen(ft_strchr(var, '=')));
	FT_INIT(int, j, ft_strlen(ft_strchr(var, '=')) - 1);
	FT_INIT(char *, name, ft_strnew(i));
	FT_INIT(char *, value, ft_strnew(j));
	name = strncpy(name, var, i);
	value = strncpy(value, ft_strchr(var, '=') + 1, j);
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

int		shell_cmds(char *cmd, char **argv)
{
	if (!cmd || !argv)
		return (0);
	if (!ft_strcmp(argv[1], "ls"))
	{
		argv[1] = NULL;
		cmd = "/bin/ls";
		execve(cmd, argv, NULL);
	}
	return (1);
}

int		distrib_functions(char **commands, t_sh *data)
{
//	if (!ft_strcmp(commands[0], "cd"))
//		shell_cd(commands);
	if (!ft_strcmp(commands[0], "env"))
		calls(data, commands);
	else if (!ft_strcmp(commands[0], "setenv"))
		calls(data, commands);
	else if (!ft_strcmp(commands[0], "unsetenv"))
		calls(data, commands);
	else if (!ft_strcmp(commands[0], "exit"))
		exit(EXIT_SUCCESS);
	else
		exit(EXIT_FAILURE);
	return (0);
}
/*
int		lsh_launch(char **args, t_sh *data)
{
	FT_INIT(char*, cmd, NULL);
	if (!args || !verif_access("/bin", args[1]))
		return (0);
	cmd = ft_strjoin("/bin/", args[0]);
	if (execve(cmd, args, data->env) == -1)
	{
		ft_putstr("minishell: command not found: ");
		ft_putendl(args[0]);
		return (0);
	}
	return (1);
}
*/
char		**lsh_read_line(char *line)
{
	char **commands;

	commands = NULL;
	if (!line)
		return (NULL);
	if (ft_strchr(line, ' '))
		commands = ft_strsplit(line, ' ');
	else
	{
		commands = (char**)malloc(sizeof(char*) * 2);
		commands[0] = line;
		commands[1] = NULL;
	}
	return (commands);
}
