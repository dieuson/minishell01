/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvirgile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/30 10:32:23 by dvirgile          #+#    #+#             */
/*   Updated: 2016/06/30 10:32:32 by dvirgile         ###   ########.fr       */
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

typedef struct 			s_sh_data
{
	int 		(*fct_tab[3])(char *cmd, char **argv);
}						t_sh_data;

#endif
