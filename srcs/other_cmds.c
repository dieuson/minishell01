/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvirgile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/26 11:46:36 by dvirgile          #+#    #+#             */
/*   Updated: 2016/07/27 14:25:49 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	if (!ft_strcmp(commands[0], "cd"))
		shell_cd(commands);
	else if (!ft_strcmp(commands[0], "env"))
		calls(data, commands);
	else if (!ft_strcmp(commands[0], "setenv"))
		calls(data, commands);
	else if (!ft_strcmp(commands[0], "unsetenv"))
		calls(data, commands);
	else if (!ft_strcmp(commands[0], "exit"))
		exit(EXIT_SUCCESS);
	return (0);
}

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
