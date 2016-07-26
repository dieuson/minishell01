/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvirgile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/27 11:40:17 by dvirgile          #+#    #+#             */
/*   Updated: 2016/07/26 12:09:30 by dvirgile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			prompt(int argc, char **argv, char **envp)
{
	FT_INIT(char*, line, NULL);
	FT_INIT(char**, commands, NULL);
	FT_INIT(int, ret, 0);
	FT_INIT(pid_t, pid, 0);
	while (1)
	{
		ret = get_next_line(0, &line);
		if (ret)
		{
			pid = fork();
			if (pid == 0)
			{
			commands = lsh_read_line(line);
			if (!ft_strcmp(commands[0], "cd"))
				shell_cd("", commands);
			else if (!ft_strcmp(commands[0], "ls"))
				lsh_launch(commands);
			free_simple_tab(&commands);
			}
			ret  = 0;
			wait(&pid);
			ft_putstr("\n$> ");
		}
	}
	if (argc || argv || envp)
		return (0);
	return (1);
}

int			main(int argc, char **argv, char **envp)
{
	t_sh	data;

	init_minishell(&data, envp);
	ft_putstr("$> ");
	if (!prompt(argc, argv, envp))
			exit(0);
	return (0);
}
