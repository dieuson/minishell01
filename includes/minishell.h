/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvirgile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/30 10:32:23 by dvirgile          #+#    #+#             */
/*   Updated: 2016/07/27 16:58:08 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		MINISHELL_H
# define	MINISHELL_H
# include <unistd.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <dirent.h>
# include <signal.h>
# include "../srcs/libft/includes/libft.h"
# include "../srcs/get_next_line/get_next_line.h"

# ifndef FT_INIT
	# define FT_INIT(t, n, v) t n = v
# endif

# ifndef FT_MULTI3
	# define FT_MULTI3(a, b, c) a = b = c
# endif

typedef struct 			s_sh
{
	char 				**env;
	char				**imp_func;
}						t_sh;

int						shell_cd(char **commands);
int						verif_access(char* path, char *file);
int						distrib_functions(char **commands, t_sh *data);

int						shell_cmds(char *cmd, char **argv);
char					**lsh_read_line(char *line);
int						lsh_launch(char **args, t_sh *data);
void					init_implement_functions(t_sh *data);
int						init_env(char ***new_env, char **envp, char *var);
void					free_env(char **env);
int						calls(t_sh *data, char **commands);

int						msh_env(t_sh *data);
int						msh_setenv(t_sh *data, char *new_var);
int						msh_unsetenv(t_sh *data, char *to_del);
int						check_varname(char *var, char *to_check);
int						env_format(char *var);

#endif










