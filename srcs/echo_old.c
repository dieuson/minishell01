/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/06 16:32:43 by sgaudin           #+#    #+#             */
/*   Updated: 2016/08/19 16:53:10 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	var_exists(t_sh *data, char *var)
{
	FT_INIT(int, i, 0);
	while (data->env[i])
	{
		if (check_varname(data->env[i], var))
		{
			ft_putstr(ft_strchr(data->env[i], '=') + 1);
			free(var);
			return (1);
		}
		i++;
	}
	free(var);
	return (0);
}

static int	recup_var(t_sh *data, char *line, int i)
{
	FT_INIT(int, j, 0);
	FT_INIT(char *, var, (char *)malloc(sizeof(char) * 200));
	i++;
	while (line[i] && line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
	{
		var[j] = line[i];
		i++;
		j++;
	}
	var[j] = '\0';
	if (ft_strlen(var) == 0)
	{
		ft_putchar('$');
		free(var);
		return (-1);
	}
	return (var_exists(data, var) == 1 ? 1 : 0);
}

int			msh_echo_env(t_sh *data, char *line)
{
	FT_INIT(int, i, 0);
	FT_INIT(int, ret, 0);
	while (line[i])
	{
		if (line[i] == '$')
			break ;
		else
			ft_putchar(line[i]);
		i++;
	}
	if (i <= (int)ft_strlen(line) && line[i] == '$')
	{
		ret = recup_var(data, line, i);
		if (ret == -1 || ret == 0)
			return (0);
		while (line && line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
			i++;
		while (line[i])
		{
			ft_putchar(line[i]);
			i++;
		}
	}
	return (1);
}

int			msh_echo(t_sh *data, char **commands)
{
	int		i;

	i = 1;
	while (commands[i])
	{
		if (ft_strchr(commands[i], '$') != NULL)
			msh_echo_env(data, commands[i]);
		else
			ft_putstr(commands[i]);
		i++;
		ft_putchar(commands[i] != NULL ? ' ' : '\n');
	}
	return (0);
}
