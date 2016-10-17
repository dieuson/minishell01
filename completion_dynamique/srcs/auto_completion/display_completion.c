#include "../../includes/ft_select.h"

static char		*set_sentence(char *str, int len_str, char *name)
{
	FT_INIT(char*, tmp, ft_itoa(len_str + 2));
	str = ft_strcat(str, "%-");
	str = ft_strcat(str, tmp);
	str = ft_strcat(str, "s");
	ft_printf(str, name);
	ft_bzero(str, ft_strlen(str));
	ft_strdel(&tmp);
	return (str);
}

void 			reset_cursor_pos(int len_str, int nb_colonnes, int nb_elem, char *sentence)
{
	FT_INIT(int, nb_col, 0);
	FT_INIT(int, nb_line, 0);
	if (!nb_elem)
		return ;
	ft_putstr("\033[32m|\033[0m");
	nb_colonnes = nb_elem <= nb_colonnes ? nb_elem : nb_colonnes;
	nb_col = (len_str + 2) * nb_colonnes - 1 - ft_strlen(sentence);
	nb_line = nb_elem / nb_colonnes;
	while (nb_col)
	{
		ft_printf("\033[1D");
		nb_col--;
	}
	while (nb_line > 0)
	{
		ft_printf("\033[1A");
		nb_line--;
	}
}

static void		display_form(t_completion *all_col, int nb_elem, int len_str, int nb_col)
{
	FT_INIT(t_file *, col, all_col->elem);
	FT_INIT(t_completion *, head, all_col);
	FT_INIT(char *, tmp, NULL);
	FT_INIT(int, ref_col, 0);
	tmp = ft_strnew(ft_strlen(col->name) + 4096);
	while (all_col && nb_elem > 0)
	{
		col = all_col->elem;
		if (col)
		{
			tmp = set_sentence(tmp, len_str, col->name);
			col = col->next;
			all_col->elem = col;
			if (!ref_col)
				head = all_col;
		}
		if (ref_col >= nb_col - 1)
		{
			ft_putendl("");
			ref_col = -1;
			all_col = head;
		}
		else
			all_col = all_col->next;
		ref_col++;
		nb_elem--;
	}
	ft_strdel(&tmp);
}

void 			display_completion(char *sentence, t_file *match_files)
{
	struct winsize ws;

	if (!sentence || !match_files)
		return ;
	ft_putstr("\n");
	FT_INIT(t_completion *, lst_lst, NULL);
	FT_INIT(int, nb_elem, match_files->nb_elem);
	FT_INIT(int, len_str, match_files->len);
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws);
	FT_INIT(int, nb_col, ws.ws_col / (len_str + 2));
	FT_INIT(int, nb_line, ws.ws_row);
	FT_INIT(int, nb_elem_lst, nb_elem / nb_col);
	lst_lst = build_lst_lst(match_files, (nb_elem_lst == 0 ? 1 : nb_elem_lst), nb_col);
	display_form(lst_lst, nb_elem, len_str, nb_col);
	ft_printf("\n%s", sentence);
	if (nb_elem || len_str || nb_col || nb_line || nb_elem_lst || lst_lst)
		return ;
}