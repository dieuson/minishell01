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

char 	*get_line(char *search, char **tab)
{
	FT_INIT(int, i, 0);
	if (!tab || !search)
		return (NULL);
	FT_INIT(int, size, ft_strlen(search));
	while (tab[i])
	{
		if (!ft_strncmp(search, tab[i], size))
			return (ft_strchr(tab[i], '=') + 1);
		i++;
	}
	return (NULL);
}

int 	get_index(char *search, char **tab)
{
	FT_INIT(int, i, 0);
	if (!tab || !search)
		return (-1);
	FT_INIT(int, size, ft_strlen(search));
	while (tab[i])
	{
		if (!ft_strncmp(search, tab[i], size))
			return (i);
		i++;
	}
	return (-1);
}

static char *set_dir_dest(char **commands, char **env)
{
	FT_INIT(char*, dir_dest, NULL);
	FT_INIT(char*, current_path, NULL);
	FT_INIT(char*, tmp, NULL);
	FT_INIT(int, len_tab, 0);
	while (commands && commands[len_tab])
		len_tab++;
	if (len_tab == 1)
		return (ft_strdup(get_line("HOME", env)));
	else if (!ft_strcmp(commands[1], "-"))
		return (ft_strjoin(get_line("OLDPWD", env), commands[1] + 1));
	else if (commands[1][0] == '~')
		return (ft_strjoin(get_line("HOME", env), commands[1] + 1));
	else if (commands[1][0] != '/')
		dir_dest = ft_strjoin("/", commands[1]);
	else
		dir_dest = ft_strdup(commands[1]);
	tmp = dir_dest;
	current_path = getcwd(NULL, 1024);
	dir_dest = ft_strjoin(current_path, dir_dest);
	ft_strdel(&tmp);
	return (dir_dest);
}

int shell_cd(char **commands, t_sh *data)
{
	FT_INIT(char*, dir_dest, NULL);
	FT_INIT(char*, current_path, NULL);
	FT_INIT(int, oldpwd, 0);
	if (!commands && data)
		return (0);
	dir_dest = set_dir_dest(commands, data->env);
	if (!verif_access(dir_dest, commands[1]))
		return (0);
	current_path = getcwd(NULL, 1024);
	oldpwd = get_index("OLDPWD", data->env);
	if (oldpwd >= 0)
	{
		free(data->env[oldpwd]);
		data->env[oldpwd] = ft_strjoin("OLDPWD=" ,current_path);
	}
	chdir(dir_dest);
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
