/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvirgile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/27 11:40:17 by dvirgile          #+#    #+#             */
/*   Updated: 2016/07/26 11:52:13 by dvirgile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void init_minishell(t_sh *data)
{
	data->env = NULL;
}

int main(int argc, char **argv, char **envp)
{
	t_sh data;
	char *line;
	char **commands;
	int ret;
	pid_t pid;

	ret = 0;
	commands = NULL;
	line = NULL;
	pid = 0;
	init_minishell(&data);
	ft_putstr("$> ");
	if (envp)
		ft_putendl(envp[0]);
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
	if (argc || argv)
		return (0);
	return (0);
}
