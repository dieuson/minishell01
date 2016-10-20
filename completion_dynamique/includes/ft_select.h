/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvirgile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/26 13:48:33 by dvirgile          #+#    #+#             */
/*   Updated: 2016/09/26 13:56:04 by dvirgile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		FT_SELECT_H

# define	FT_SELECT_H
# include "../libft/includes/libft.h"
# include "../srcs/ft_printf/includes/ft_printf.h"
# include "../srcs/get_next_line/get_next_line.h"
# include <sys/ioctl.h>
# include <termios.h>
# include <curses.h>
# include <term.h>
# include <stdio.h>
# include <sys/types.h>
# include <dirent.h>


typedef struct				s_file
{
	char					*name;
	int 					type;
	int 					len;
	char 					*absolute_path;
	int 					nb_elem;
	struct s_file			*next;
}							t_file;

typedef struct				s_completion
{
	struct s_file 			*elem;
	struct s_completion		*next;
}							t_completion;

typedef struct				s_shell
{
	char					*buf;
}							t_shell;


void 						free_lists(t_file *match_files);
void						free_auto_tab(char **table);
t_file						*sort_list(t_file *files);
char 						*default_sentence(char *sentence);
char						*detect_auto_comletion(char *sentence);
t_file 						*store_files_dirs(DIR *rep, t_file *files, char *path, char *to_search);
t_file 						*compare_list_sentence(t_file *files, char *sentence);
char 						**set_path(char **sentence, char *home, char *current_path);
void 						display_completion(char *sentence, t_file *match_files);
t_completion 				*build_lst_lst(t_file *match_files, int nb_elem, int nb_col);
char 						*similarity(t_file *match_files, char *sentence);

#endif