/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvirgile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/26 11:29:38 by dvirgile          #+#    #+#             */
/*   Updated: 2016/07/26 11:48:17 by dvirgile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int shell_cd(char *cmd, char **argv)
{
	char *current_path;
	char *dir_dest;
	char *tmp;

	if (!cmd || !argv)
		return (0);
	dir_dest = ft_strjoin("/", argv[1]);
	tmp = dir_dest;
	current_path = getcwd(NULL, 1024);
	if (!current_path)
		perror("Minishell");
	//printf("path =%s,\n", current_path);
	dir_dest = ft_strjoin(current_path, dir_dest);
	//ft_strdel(&tmp);
	chdir(dir_dest);
	current_path = getcwd(NULL, 1024);
	//printf("path =%s,\n", current_path);
	//ft_strdel(&dir_dest);
	return (1);
}

char **lsh_read_line(char *line)
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
