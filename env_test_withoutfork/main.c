/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/06 15:37:18 by sgaudin           #+#    #+#             */
/*   Updated: 2016/08/06 15:52:55 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		main(int ac, char **av, char **envp)
{
	t_sh	*data;

	FT_INIT(char *, line, NULL);
	FT_INIT(char **, commands, NULL);
	FT_INIT(int, ret, 0);
	data = (t_sh *)malloc(sizeof(t_sh));
	init_env(&(data->env), envp, NULL);
	if (ac && av)
		ft_putstr("$> ");
	while (1)
	{
		ret = get_next_line(0, &line);
		if (ret)
		{
			commands = lsh_read_line(line);
			distrib_functions(commands, data);
			free_simple_tab(&commands);
		}
		ret = 0;
		ft_putstr("\n$> ");
	}
	return (0);
}
