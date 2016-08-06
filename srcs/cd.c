/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvirgile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/26 11:29:38 by dvirgile          #+#    #+#             */
/*   Updated: 2016/07/28 17:18:36 by dvirgile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int error_cd(char *type, char *file)
{
	ft_putstr("cd: ");
	ft_putstr(type);
	ft_putstr(": ");
	ft_putendl(file);
	return (0);
}

int		verif_access(char *path, char *file)
{
	struct stat infos;

	lstat(path, &infos);
	if (access(path, F_OK) != 0)
		return (error_cd("no such file or directory", file));
	else if (access(path, X_OK) != 0 || !S_ISDIR(infos.st_mode))
		return (error_cd("permission denied", file));
	else if (!S_ISDIR(infos.st_mode))
		return (error_cd("not a directory", file));
	return (1);
}

int shell_cd(char **commands)
{
	FT_INIT(char*, tmp, NULL);
	FT_INIT(char*, dir_dest, NULL);
	FT_INIT(char*, current_path, NULL);
	if (!commands)
		return (0);
	if (commands[1][0] != '/')
		dir_dest = ft_strjoin("/", commands[1]);
	else
		dir_dest = ft_strdup(commands[1]);
	tmp = dir_dest;
	current_path = getcwd(NULL, 1024);
	if (!current_path)
		return (error_cd("current directory not found!", commands[1]));
	dir_dest = ft_strjoin(current_path, dir_dest);
	ft_strdel(&tmp);
	if (!verif_access(dir_dest, commands[1]))
		return (0);
	chdir(dir_dest);
	current_path = getcwd(NULL, 1024);
	ft_strdel(&dir_dest);
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
