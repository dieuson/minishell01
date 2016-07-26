/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvirgile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/30 10:32:23 by dvirgile          #+#    #+#             */
/*   Updated: 2016/07/26 14:37:05 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		MINISHELL_H
# define	MINISHELL_H
# include <unistd.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "../srcs/libft/includes/libft.h"
# include "../srcs/get_next_line/get_next_line.h"

# ifndef FT_INIT
	# define FT_INIT(t, n, v) t n = v
# endif

typedef struct 			s_sh
{
	char 				**env;
}						t_sh;

int						shell_cd(char *cmd, char **argv);
int						shell_cmds(char *cmd, char **argv);
char					**lsh_read_line(char *line);
int						lsh_launch(char **args);
int						init_env(char ***new_env, char **envp, char *var);
void					free_env(char **env);
int						calls(t_sh *data, char **commands);

int						msh_env(t_sh *data);
int						msh_setenv(t_sh *data, char *new_var);
int						msh_unsetenv(t_sh *data, char *to_del);

#endif










