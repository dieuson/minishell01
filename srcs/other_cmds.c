/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvirgile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/26 11:46:36 by dvirgile          #+#    #+#             */
/*   Updated: 2016/07/26 13:55:32 by sgaudin          ###   ########.fr       */
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

int		lsh_launch(char **args)
{
	int i;
	char *tmp;

	tmp = NULL;
	i = 0;
	if (!args)
		return (0);
	while (args[i])
	{
		if (args[i] && !ft_strcmp(args[i], "ls"))
		{
			tmp = args[i];
			args[i] = ft_strdup("/bin/ls");
			ft_strdel(&tmp);
		}
		i++;
	}
	execve(args[0], args, NULL);
	return (1);
}
