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

int my_outc(int c)
{
	ft_putchar(c);
	return (0);
}



int main()
{
	struct termios *termios_p;
	struct termios *init_term;
	char            *term_name;
 //   struct winsize w;

	term_name = NULL;
	FT_INIT(int, val, 0);
	FT_INIT(int, fd_test, 0);
	FT_INIT(int, fd_result, 0);
	FT_INIT(char*, test, NULL);
	FT_INIT(char*, result, NULL);

	FT_INIT(int, i, 1);
	FT_INIT(char*, line, ft_strnew(8));
	FT_INIT(char*, inputs, "");
	FT_INIT(char*, tmp, NULL);

    if ((term_name = getenv("TERM")) == NULL)
        return (1);

// 	ft_putstr("Minishell ready\n");
 //	ft_putendl(term_name);
	termios_p = (struct termios *)malloc(sizeof(struct termios));
//	init_term = (struct termios *)malloc(sizeof(struct termios));

	ft_get_termattr(&init_term);

	termios_p->c_lflag &= ~(ICANON); // Mode canonique
	termios_p->c_lflag &= ~(ECHO); // Effectuer un écho des caractères saisis. Si ICANON est également activé, la touche ERASE efface le caractère précédent, et WERASE efface le mot précédent.
	termios_p->c_lflag &= ~(ISIG); // Lorsqu'un caractère INTR, QUIT, SUSP ou DSUSP arrive, engendrer le signal correspondant.
	termios_p->c_cc[VMIN] = 1;
	termios_p->c_cc[VTIME] = 0;

    if (tgetent(NULL, term_name) == ERR)
        return (1);

// 	tcsetattr(STDIN_FILENO, TCSANOW, termios_p);
 	tcsetattr(STDIN_FILENO, TCSANOW, init_term);
 	fd_result = open("/home/dieuson/minishell01/completion_dynamique/srcs/result.txt",  O_RDONLY);
 	fd_test = open("/home/dieuson/minishell01/completion_dynamique/srcs/test.txt",  O_RDONLY);
 	while (get_next_line(fd_test, &test))
 	{
		inputs = test;
		inputs = detect_auto_comletion(inputs);
		get_next_line(fd_result, &result);
		ft_printf("inputs =%s,\n", test);
		if (inputs)
			ft_printf("output =%s,\n", inputs);
		else
			ft_printf("NO INPUTS\n");
		if (result)
			ft_printf("result =%s,\n", result);
		else
			ft_printf("NO LINE\n");
		if (result && inputs && !ft_strcmp(result, inputs))
			ft_putstr("\033[32mOK\033[0m\n");
		else
			ft_putstr("\033[31mKO\033[0m\n");
 		ft_strdel(&inputs);
 		ft_strdel(&test);
 		i++;
 	}
 	close(fd_result);
 	close(fd_test);
	return (0);
	while (1)
	{
		if (read(STDIN_FILENO, line, 16) > 0)
		{
			tcsetattr(STDIN_FILENO, TCSANOW, init_term);
		    val = *line;
			if (val == 9)
				inputs = detect_auto_comletion(inputs);
			else
			{
				tmp = inputs;
				inputs = ft_strjoin(tmp, line);
				if (tmp && ft_strlen(tmp))
					ft_strdel(&tmp);
			    ft_putstr(line);
			}
			if (inputs && ft_strstr(inputs, "exit"))
				break;
			if (inputs && ft_strstr(inputs, "echap"))
				break;
			val = 0;
			tcsetattr(STDIN_FILENO, TCSANOW, termios_p);
		}
	}
	tcsetattr(STDIN_FILENO, TCSANOW, init_term);
	if (line && ft_strlen(line))
		ft_strdel(&line);
//	ft_set_termattr(&init_term);
	return (0);
}
