/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvirgile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/27 11:40:17 by dvirgile          #+#    #+#             */
/*   Updated: 2016/07/26 17:10:53 by dvirgile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			verif_implements(char *cmd, t_sh *data)
{
	FT_INIT(char**, functions, data->imp_func);
	FT_INIT(int, i, 0);
	while (functions[i])
	{
		if (!ft_strcmp(cmd, functions[i]))
			return (1);
		i++;
	}
	return (0);
}

int			prompt(t_sh *data)
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
				if (verif_implements(commands[0], data))
					distrib_functions(commands, data);
				else
					lsh_launch(commands, data);
				free_simple_tab(&commands);
			}
			ret  = 0;
			wait(&pid);
			ft_putstr("\n$> ");
		}
	}
	return (1);
}

int			main(int argc, char **argv, char **envp)
{
	t_sh	*data;

	data = (t_sh *)malloc(sizeof(t_sh));
	init_implement_functions(data);
	init_env(&(data->env), envp, NULL);
	ft_putstr("$> ");
	if (!prompt(data))
			exit(0);
	free(data);
	free_env(data->imp_func);
	if (argc || argv)
		return (1);
	return (0);
}
