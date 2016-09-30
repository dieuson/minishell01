/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvirgile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/27 15:11:31 by dvirgile          #+#    #+#             */
/*   Updated: 2016/09/27 15:15:57 by dvirgile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"


int			ft_get_termattr(struct termios **term)
{
	int		ret;

	if (!(*term = (struct termios *)malloc(sizeof(struct termios))))
		ft_putstr("ft_get_termattr error malloc term");
	if ((ret = tcgetattr(STDIN_FILENO, *term)) != 0)
		ft_putstr("ft_get_termattr error tcgetattr");
	return (ret);
}

int			ft_set_termattr(struct termios **term)
{
	int		ret;

	if ((ret = tcsetattr(0, TCSADRAIN, *term)) != 0)
		ft_putstr("ft_set_termattr error tcsetattr");
	return (ret);
}

int main()
{
	struct termios *termios_p;
	struct termios *init_term;
	char            *term_name;

	term_name = NULL;
	FT_INIT(int, ret, 0);
	FT_INIT(int, init_fd, 0);
	FT_INIT(char*, line, NULL);
	FT_INIT(char*, tmp, "");

    if ((term_name = getenv("TERM")) == NULL)
        return (1);
    if (tgetent(NULL, term_name) == ERR)
        return (1);

 	ft_putstr("Minishell ready\n");
	termios_p = (struct termios *)malloc(sizeof(struct termios));
	init_term = (struct termios *)malloc(sizeof(struct termios));

	init_fd = ft_get_termattr(&init_term);

	termios_p->c_lflag &= ~(ICANON); // Mode canonique
	termios_p->c_lflag &= ~(ECHO); // Effectuer un écho des caractères saisis. Si ICANON est également activé, la touche ERASE efface le caractère précédent, et WERASE efface le mot précédent.
	termios_p->c_lflag &= ~(ISIG); // Lorsqu'un caractère INTR, QUIT, SUSP ou DSUSP arrive, engendrer le signal correspondant.
//	termios_p->c_cc[VMIN] = 1;
//	termios_p->c_cc[VTIME] = 0;



 	tcsetattr(STDIN_FILENO, TCSANOW, termios_p);
//	ft_set_termattr(&termios_p);

	while (1)
	{
		ret = get_next_line(0, &line);
//		if (!ft_strcmp(line, "exit"))
//			return(ft_set_termattr(&init_term));
		if (ft_strstr(tmp, "exit"))
		{
			ft_set_termattr(&init_term);
			exit(0);
		}
		if (ret && ft_strlen(line))
		{
			if (!ft_strcmp(line, "^["))
			{
					ft_putstr("ECHAP\n");
					ft_set_termattr(&init_term);
					exit(0);
			}
			if (!ft_strcmp(line, "\t"))
				ft_putstr("tabulation\n");
//			ft_strdel(&line);
			ret = 0;
			tmp = ft_strjoin(tmp, line);
			ft_putendl(tmp);
		}
	}
//	ft_set_termattr(&init_term);
	return (0);
}
